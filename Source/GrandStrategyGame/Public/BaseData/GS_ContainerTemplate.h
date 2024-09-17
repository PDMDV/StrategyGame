#pragma once

#include "CoreMinimal.h"

template <class TContainer, class TElement>
class TContainerFunctions
{
	typedef decltype(TElement::Type) TType;
	typedef decltype(TElement::Amount) TAmount;
	
protected:
	
	static int32 FindIndexT(TContainer& Container, TType Object)
	{
		int32 Index = 0;
		for(TElement& Element : Container.GetArray())
		{
			if(Element.Type == Object)
			{
				return Index;
			}
			Index++;
		}
		return INDEX_NONE;
	}
	
	static void AddT(TContainer& Container, TElement Element)
	{
		int32 Index = FindIndexT(Container, Element.Type);
		if(Index == INDEX_NONE)
		{
			Container.GetArray().Add(Element);
		}
		else
		{
			Container.GetArray()[Index].Amount += Element.Amount;
		}
	}

	static TAmount SubtractT(TContainer& Container, TElement Element)
	{
		int32 Index = FindIndexT(Container, Element.Type);
		if(Index == INDEX_NONE)
		{
			return Element.Amount;
		}
		Container.GetArray()[Index].Amount -= Element.Amount;
		if(Container.GetArray()[Index].Amount < 0)
		{
			TAmount Rest = FMath::Abs(Container.GetArray()[Index].Amount);
			Container.GetArray()[Index].Amount = 0;
			return Rest;
		}
		return 0;
	}
	
	static void MergeT(TContainer& Target, TContainer& Source)
	{
		for(const TElement& Element : Source.GetArray())
		{
			AddT(Target, Element);
		}
	}

	static TContainer CombineT(TContainer& First, TContainer& Second)
	{
		TContainer Result;
		MergeT(Result, First);
		MergeT(Result, Second);
		return Result;
	}
	
	static void ClearT(TContainer& Container)
	{
		Container.GetArray().Empty();
	}
	
	static TElement GetT(TContainer& Container, TType Object)
	{
		int32 Index = FindIndexT(Container, Object);
		if(Index != INDEX_NONE)
		{
			return Container.GetArray()[Index];
		}
		return TElement(Object, 0);
	}
	
	static TElement MultiplyT(TElement Element, float Multiplier)
	{
		float NewAmount = Element.Amount * Multiplier; 
		return TElement(Element.Type, NewAmount);
	}
	
	static TContainer MultiplyContainerT(TContainer Container, float Multiplier)
	{
		TContainer Result;
		for(TElement Element : Container.GetArray())
		{
			AddT(Result, MultiplyT(Element, Multiplier));
		}
		return Result;
	}
	
	static bool HasTypeT(TContainer& Container, TType Type)
	{
		return FindIndexT(Container, Type) != INDEX_NONE;
	}
	
	static bool ContainsT(TContainer& Source, TContainer& Target)
	{
		for(TElement Element : Source.GetArray())
		{
			if( GetT(Target, Element.Type).Amount > Element.Amount)
			{
				return false;
			}
		}
		return true;
	}
	
	static TArray<TType> GetAllTypesT(TContainer& Container)
	{
		TArray<TType> Result;
		for(TElement& Element : Container.GetArray())
		{
			Result.Add(Element.Type);
		}
		return Result;
	}

	static TSet<TType> GetAllTypesSetT(TContainer& Container)
	{
		TSet<TType> Result;
		for(TElement& Element : Container.GetArray())
		{
			Result.Add(Element.Type);
		}
		return Result;
	}
	
	static TAmount GetTotalSizeT(TContainer& Container)
	{
		TAmount TotalSize = 0;
		for(const TElement& Element : Container.GetArray())
		{
			TotalSize += Element.Amount;
		}
		return TotalSize;
	}
	
	static TContainer NegateT(TContainer& Container)
	{
		TContainer Result;
		for(const TElement& Element : Container.GetArray())
		{
			AddT(Result, TElement(Element.Type, -Element.Amount));
		}
		return Result;
	}

	static bool IsEmptyT(TContainer& Container)
	{
		return Container.GetArray().IsEmpty();
	}

	static bool IsNotEmptyT(TContainer& Container)
	{
		return !Container.GetArray().IsEmpty();
	}

	static TContainer MakeContainerT(const TElement& Element)
	{
		TContainer Container;
		Container.GetArray().Add(Element);
		return Container;
	}
};
