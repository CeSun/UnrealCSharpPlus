﻿#pragma once

template <typename T, typename Enable = void>
struct TDefaultArgument
{
};

template <typename T>
struct TDefaultArgumentBuilder
{
	static FString GetImplementation(const bool bIsFirst)
	{
		return {};
	}

	template <typename DefaultArgument, typename... Args>
	static FString GetImplementation(const bool bIsFirst, DefaultArgument InDefaultArgument, Args&&... InParams)
	{
		return (bIsFirst ? TEXT("") : TEXT(" ,")) +
			TDefaultArgument<DefaultArgument, DefaultArgument>::Get(InDefaultArgument) +
			GetImplementation(false, InParams...);
	}

	template <typename... Args>
	static FString Get(Args&&... InDefaultArguments)
	{
		return FString::Printf(TEXT(
			"new %s(%s)"),
		                       *TName<T, T>::Get(),
		                       *GetImplementation(true, InDefaultArguments...)
		);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>, T>>
{
	static FString Get(const uint8 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>, T>>
{
	static FString Get(const uint16 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>, T>>
{
	static FString Get(const uint32 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>, T>>
{
	static FString Get(const uint64 InValue)
	{
		return FString::Printf(TEXT("%lld"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>, T>>
{
	static FString Get(const int8 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>, T>>
{
	static FString Get(const int16 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>, T>>
{
	static FString Get(const int32 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>, T>>
{
	static FString Get(const int64 InValue)
	{
		return FString::Printf(TEXT("%lld"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>, T>>
{
	static FString Get(const bool InValue)
	{
		return InValue ? TEXT("true") : TEXT("false");
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>, T>>
{
	static FString Get(const float InValue)
	{
		return FString::Printf(TEXT("%sf"), *FString::SanitizeFloat(InValue));
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>, T>>
{
	static FString Get(const FName& InValue)
	{
		return FString::Printf(TEXT(
			"new %s(\"%s\")"),
		                       *TName<T, T>::Get(),
		                       *InValue.ToString()
		);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>, T>>
{
	static FString Get(const FString& InValue)
	{
		return FString::Printf(TEXT(
			"new %s(\"%s\")"),
		                       *TName<T, T>::Get(),
		                       *InValue
		);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>, T>>
{
	static FString Get(const FText& InValue)
	{
		return FString::Printf(TEXT(
			"new %s(\"%s\")"),
		                       *TName<T, T>::Get(),
		                       *InValue.ToString()
		);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, double>, T>>
{
	static FString Get(const double InValue)
	{
		return FString::SanitizeFloat(InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FRotator>, T>>
{
	static FString Get(const FRotator& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.Pitch, InValue.Yaw, InValue.Roll);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FQuat>, T>>
{
	static FString Get(const FQuat& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.X, InValue.Y, InValue.Z, InValue.W);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FVector>, T>>
{
	static FString Get(const FVector& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.X, InValue.Y, InValue.Z);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FTransform>, T>>
{
	static FString Get(const FTransform& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.GetRotation(), InValue.GetTranslation(), InValue.GetScale3D());
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FLinearColor>, T>>
{
	static FString Get(const FLinearColor& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.R, InValue.G, InValue.B, InValue.A);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FColor>, T>>
{
	static FString Get(const FColor& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.R, InValue.G, InValue.B, InValue.A);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FPlane>, T>>
{
	static FString Get(const FPlane& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.X, InValue.Y, InValue.Z, InValue.W);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FVector2D>, T>>
{
	static FString Get(const FVector2D& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.X, InValue.Y);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FVector4>, T>>
{
	static FString Get(const FVector4& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.X, InValue.Y, InValue.Z, InValue.W);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FGuid>, T>>
{
	static FString Get(const FGuid& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.A, InValue.B, InValue.C, InValue.D);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FBox2D>, T>>
{
	static FString Get(const FBox2D& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.Min, InValue.Max);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>>
{
	static FString Get(const TMap<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
	                              typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>>& InValue)
	{
		auto Value = FString::Printf(TEXT(
			"new %s{"),
		                             *TName<T, T>::Get()
		);

		auto bIsFirst = true;

		for (const auto& Iterator : InValue)
		{
			Value += FString::Printf(TEXT(
				"%s{%s, %s}"),
			                         bIsFirst ? TEXT("") : TEXT(" ,"),
			                         *TDefaultArgument<
				                         typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
				                         typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
			                         ::Get(Iterator.Key),
			                         *TDefaultArgument<
				                         typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>,
				                         typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>>
			                         ::Get(Iterator.Value)
			);

			bIsFirst = false;
		}

		Value += TEXT("}");

		return Value;
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value, T>>
{
	static FString Get(const TSet<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>& InValue)
	{
		auto Value = FString::Printf(TEXT(
			"new %s{"),
		                             *TName<T, T>::Get()
		);

		auto bIsFirst = true;

		for (const auto& Iterator : InValue)
		{
			Value += FString::Printf(TEXT(
				"%s%s"),
			                         bIsFirst ? TEXT("") : TEXT(" ,"),
			                         *TDefaultArgument<
				                         typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
				                         typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
			                         ::Get(Iterator)
			);

			bIsFirst = false;
		}

		Value += TEXT("}");

		return Value;
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>>
{
	static FString Get(const TArray<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>& InValue)
	{
		auto Value = FString::Printf(TEXT(
			"new %s{"),
		                             *TName<T, T>::Get()
		);

		auto bIsFirst = true;

		for (const auto& Iterator : InValue)
		{
			Value += FString::Printf(TEXT(
				"%s%s"),
			                         bIsFirst ? TEXT("") : TEXT(" ,"),
			                         *TDefaultArgument<
				                         typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
				                         typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
			                         ::Get(Iterator)
			);

			bIsFirst = false;
		}

		Value += TEXT("}");

		return Value;
	}
};
