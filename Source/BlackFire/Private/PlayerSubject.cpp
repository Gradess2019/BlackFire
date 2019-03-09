// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerSubject.h"

// Add default functionality here for any IPlayerSubject functions that are not pure virtual.

void IPlayerSubject::AttachObserver(IPlayerObserver* newObserver)
{
	if (newObserver)
	{
		observers.Add(newObserver);
	}
}

void IPlayerSubject::DetachObserver(IPlayerObserver* observer)
{
	if (observer && observers.Find(observer))
	{
		observers.Remove(observer);
	}
}

void IPlayerSubject::Notify()
{
	for (IPlayerObserver* observer : observers)
	{
		observer->Update(this);
	}
}