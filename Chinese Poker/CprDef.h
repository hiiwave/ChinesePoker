/****************************************************************************
FileName   [ CprDef.h ]
Synopsis   [ define basic var for Cpr package ]
****************************************************************************/

#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <string>
using namespace std;

class CprCollection;
class CprPlayer;
class CprHand;
class CprCard;
class CprDealer;

typedef vector<CprCollection> CollectionList;
typedef vector<CprPlayer*>		PlayerList;
typedef vector<CprHand>			HandList;
typedef vector<CprCard>			CardList;

#define FRIEND_ALL_MASTER					\
friend class CprHandMaster;				\
friend class CprStraightFlushMaster;	\
friend class CprFourOfAKindMaster;		\
friend class CprFullHouseMaster;			\
friend class CprFlushMaster;				\
friend class CprStraightMaster;			\
friend class CprThreeOfAKindMaster;		\
friend class CprTwoPairMaster;			\
friend class CprOnePairMaster;			\
friend class CprHighCardMaster;			\
template <class S> friend class CprEachMasterTest;	\

