// CharUtils.cpp
// Utilities for a single character.

#include "CharUtils.h"


CharUtils::CharUtils()
{
}


CharUtils::~CharUtils()
{
}


/* static */ char CharUtils::ToUpper(char ch)
{
	return ch >= 'a' && ch <= 'z' ? ch - ('a' - 'A') : ch;
}


/* static */ char CharUtils::ToLower(char ch)
{
	return ch >= 'A' && ch <= 'Z' ? ch + ('a' - 'A') : ch;
}
