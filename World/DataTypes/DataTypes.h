#pragma once
#ifndef DATA_TYPES_HEADER
#define DATA_TYPES_HEADER
#include "../WorldExt/Country.h"
#include "../WorldExt/Province.h"
#include "../WorldExt/State.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

/**
 * @brief Структура взаимодействи одной страны на другую.
*/
typedef struct TargetCountry
{
	std::string CountryTag;			/**< Тэг страны, который производит действие. */
	std::string TargetCountryTag;	/**< Тэг страны, к которой производится действие. */
};

/**
 * @brief Структура отношения стран.
*/
typedef struct Diplomatic
{
	TargetCountry Target;	/**< Пара стран. */
	double Relations;		/**< Значительность отношений. */
};

/**
 * @brief Структура закупок стран.
*/
typedef struct Purchase
{
	TargetCountry Target;	/**< Пара стран. */
	Resources Resource;		/**< Покупаемый ресурс. */
	double Amount;			/**< Количество ресурса. */
};	

/**
 * @brief Структура запрета продажи ресурсов.
*/
typedef struct Embargo
{
	TargetCountry Target;	/**< Пара стран. */
	Resources Resource;		/**< Запрещаемый ресурс. */
};

/**
 * @brief Структура договора о ненападении.
*/
typedef struct NonAggressionPact
{
	TargetCountry Target;				/**< Пара стран. */
	boost::posix_time::ptime EndDate;	/**< Дата конца договора. */
};

/**
 * @brief Структура определяющая государственный долг стран.
*/
typedef struct Stocks
{
	TargetCountry Target;	/**< Пара стран. */
	long double Amount;		/**< Сумма долга. */
};

/**
 * @brief Структура займов стран.
*/
typedef struct Loan
{
	TargetCountry Target;	/**< Пара стран. */
	long double Amount;		/**< Сумма займа. */
};

/**
 * @brief Структура союза стран.
*/
typedef struct Union
{
	std::string Name;						/**< Название альянса. */
	std::string Owner;						/**< Тэг страны - главы альянса. */
	std::vector<std::string> Members;		/**< Тэг стран - участниц альянса. */
};

#endif