#pragma once

namespace EscapeRoom
{
	template <typename Object, typename Return, typename ...Args>
	using MemberFunction = Return(Object::*)(Args...);

	using MemberObjectType = void*;

#define MEMBER_FUNC_TYPE MemberFunction<Object, Return, Args...>

	template <typename Object, typename Return, typename ...Args>
	struct MemberFunctionCallback
	{
	private:
		MemberObjectType member_object;    // Object that owns the member function
		MEMBER_FUNC_TYPE mfc;              // A pointer to member function

	public:
		explicit inline MemberFunctionCallback(MemberObjectType object_, MEMBER_FUNC_TYPE mfc_) :
			member_object(object_),
			mfc(mfc_)
		{
		}

		inline Return Invoke(Args&& ...args_)
		{
			return (static_cast<Object*>(member_object)->*mfc)(std::forward<Args>(args_)...);
		}
	};

	template <typename Return, typename ...Args >
	struct DelegateBase
	{
		virtual ~DelegateBase() = default;
		virtual Return Invoke(Args&&... args_) = 0;
	};

	template <typename Object, typename Return, typename... Args>
	class Delegate : public DelegateBase<Return, Args...>
	{
	private:
		std::unique_ptr<MemberFunctionCallback<Object, Return, Args...>> callback_;

	public:
		inline Delegate() = default;

		inline void Register(MemberObjectType object_, MEMBER_FUNC_TYPE func_)
		{
			callback_ = std::make_unique<MemberFunctionCallback<Object, Return, Args...>>(object_, func_);
		}

		inline Return Invoke(Args&&... args_) override
		{
			return callback_->Invoke(std::forward<Args>(args_)...);
		}

		inline bool HasCallback() const
		{
			return callback_ != nullptr;
		}
	};

	template <typename Return, typename ...Args>
	class Signal final
	{
	private:
		std::unordered_map<unsigned int, std::unique_ptr<DelegateBase<Return, Args...>>> slots;

	public:
		template <typename Object>
		inline void Connect(Object* member_object_, MEMBER_FUNC_TYPE slot_)
		{
			// Make delegate base
			auto ptr = std::make_unique<Delegate<Object, Return, Args...>>();
			ptr->Register(member_object_, slot_);

			slots.insert(std::make_pair(0, std::move(ptr)));
		}

		inline void Disconnect(const unsigned int id_)
		{
			if (slots.find(id_) != slots.end()) // Check if signal has slot
			{
				slots.erase(id_);
			}
		}

		inline void EmitAll(Args&& ...args_)
		{
			for (const auto& ptr : slots)
			{
				ptr.second->Invoke(std::forward<Args>(args_)...);
			}
		}
	};
}