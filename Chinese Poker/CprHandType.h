/****************************************************************************
FileName   [ CprHandType.h ]
Synopsis   [ define each hand type of a poker game ]
****************************************************************************/

#pragma once

#define HTHighestType	10
#define HTLowestType	2

enum HandType {
	HTUltraStraightFlush = 11,	// calc subscore only
	HTStraightFlush = 10,
	HTFourOfAKind = 9,
	HTFullHouse = 8,
	HTFlush = 7,
	HTStraight = 6,
	HTThreeOfAKind = 5,
	HTTwoPair = 4,
	HTOnePair = 3,
	HTHighCard = 2,
	HTXianggong = 1,
	HTUndefined = 0
};