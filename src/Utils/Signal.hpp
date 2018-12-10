/*
** EPITECH PROJECT, 2018
** GameEngine
** File description:
** GUI / Signal.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

template <typename... Args>
class Signal;

////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <list>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

template <typename... Args>
class Signal
{
	class ISlot
	{
	public:
		virtual ~ISlot() {}
		virtual void emit(Args...) = 0;
	};

	////////////////////////////////////////

	class Slot_STLFunction : public ISlot
	{
	public:
		Slot_STLFunction(std::function<void(Args...)> function)
		: m_function(function)
		{}

		~Slot_STLFunction() override {}

		void emit(Args... args) override {
			m_function(std::forward<Args>(args)...);
		}

	private:
		std::function<void(Args...)> m_function;
	};

	////////////////////////////////////////

	template <typename T>
	class Slot_ClassMember : public ISlot
	{
	public:
		Slot_ClassMember(T *classPtr, void (T::*classMember)(Args...))
		: m_classPtr(classPtr)
		, m_classMember(classMember)
		{}

		~Slot_ClassMember() override {}

		void emit(Args... args) override {
			(m_classPtr->*m_classMember)(std::forward<Args>(args)...);
		}

	private:
		T *m_classPtr;
		void (T::*m_classMember)(Args...);
	};

	////////////////////////////////////////

	class Slot_Function : public ISlot
	{
	public:
		Slot_Function(void (*function)(Args...))
		: m_function(function)
		{}

		~Slot_Function() override {}

		void emit(Args... args) override {
			(*m_function)(std::forward<Args>(args)...);
		}

	private:
		void (*m_function)(Args...);
	};

	////////////////////////////////////////

public:
	typedef std::shared_ptr<ISlot> SlotPtr;
	typedef std::list<SlotPtr> SlotContainer;

public:
	Signal() {}

public:
	void connect(std::function<void(Args...)> function) {
		connect(std::make_shared<Slot_STLFunction>(function));
	}

	template <typename T>
	void connect(T *classPtr, void (T::*classMember)(Args...)) {
		connect(std::make_shared<Slot_ClassMember<T>>(classPtr, classMember));
	}

	void connect(void (*function)(Args...)) {
		connect(std::make_shared<Slot_Function>(function));
	}

	void connect(SlotPtr slot) {
		m_slots.push_back(slot);
	}

	void connect(const Signal<Args...> &other) {
		for (auto &handler : other.getSlots())
			connect(handler);
	}

	void clear() {
		m_slots.clear();
	}

	void emit(Args... args) {
		for (auto &slot : m_slots)
			slot->emit(std::forward<Args>(args)...);
	}

	const SlotContainer &getSlots() const {
		return m_slots;
	}


	void operator ()(Args... args) {
		emit(std::forward<Args>(args)...);
	}

private:
	SlotContainer m_slots;
};