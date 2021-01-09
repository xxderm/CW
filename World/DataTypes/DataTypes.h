#pragma once
#ifndef DATA_TYPES_HEADER
#define DATA_TYPES_HEADER
#include "../WorldExt/Country.h"
#include "../WorldExt/Province.h"
#include "../WorldExt/State.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

/**
 * @brief ��������� ������������� ����� ������ �� ������.
*/
typedef struct TargetCountry
{
	std::string CountryTag;			/**< ��� ������, ������� ���������� ��������. */
	std::string TargetCountryTag;	/**< ��� ������, � ������� ������������ ��������. */
};

/**
 * @brief ��������� ��������� �����.
*/
typedef struct Diplomatic
{
	TargetCountry Target;	/**< ���� �����. */
	double Relations;		/**< �������������� ���������. */
};

/**
 * @brief ��������� ������� �����.
*/
typedef struct Purchase
{
	TargetCountry Target;	/**< ���� �����. */
	Resources Resource;		/**< ���������� ������. */
	double Amount;			/**< ���������� �������. */
};	

/**
 * @brief ��������� ������� ������� ��������.
*/
typedef struct Embargo
{
	TargetCountry Target;	/**< ���� �����. */
	Resources Resource;		/**< ����������� ������. */
};

/**
 * @brief ��������� �������� � �����������.
*/
typedef struct NonAggressionPact
{
	TargetCountry Target;				/**< ���� �����. */
	boost::posix_time::ptime EndDate;	/**< ���� ����� ��������. */
};

/**
 * @brief ��������� ������������ ��������������� ���� �����.
*/
typedef struct Stocks
{
	TargetCountry Target;	/**< ���� �����. */
	long double Amount;		/**< ����� �����. */
};

/**
 * @brief ��������� ������ �����.
*/
typedef struct Loan
{
	TargetCountry Target;	/**< ���� �����. */
	long double Amount;		/**< ����� �����. */
};

/**
 * @brief ��������� ����� �����.
*/
typedef struct Union
{
	std::string Name;						/**< �������� �������. */
	std::string Owner;						/**< ��� ������ - ����� �������. */
	std::vector<std::string> Members;		/**< ��� ����� - �������� �������. */
};

#endif