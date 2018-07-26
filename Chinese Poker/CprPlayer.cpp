/****************************************************************************
FileName   [ CprPlayer.cpp ]
Synopsis   [ implement CprPlayer member functions ]
****************************************************************************/

#include "CprPlayer.h"
#include "CprHandMaster.h"
#include "CprHand.h"

CprPlayer::CprPlayer() {
}

CprPlayer::CprPlayer(string id)
	: _id (id) {}

CprPlayer::~CprPlayer() {
}

void CprPlayer::strategy() {
	playerStrategy();
	collection().finishSetting();
}

const CprHand& CprPlayer::getHand(int idx) const {
	return _collection.getHand(idx);
}

CprHand & CprPlayer::hand(int idx) {
	return _collection.hand(idx);
}

void CprPlayer::winOneTrick(CprPlayer * player) {
	++_score;
	--player->_score;
}

void CprPlayer::gunShooting(CprPlayer * player) {
	_score += 3;
	player->_score -= 3;
	cout << *this << " (+3) shoots " << *player << " (-3)" << endl;
}

void CprPlayer::setId(string str) {
	_id = str;
}

string CprPlayer::getId() const {
	return _id;
}

void CprPlayer::printId(int pType) const {
	if (pType == 0) {
		cout << getId();
	} else {
		cout << getId() << setw(10 - getId().length()) << ": ";
	}
}

int CprPlayer::getScore() const {
	return _score;
	return 0;
}

void CprPlayer::printScore() const {
	cout << _id << "'s score " << _score << endl;
}

void CprPlayer::reset() {
	_collection = CprCollection();
}

CprCollection & CprPlayer::collection() {
	return _collection;
}

const CprCollection & CprPlayer::collection() const {
	return _collection;
}

void CprPlayer::assertValidStrategy() const {
	if (CprHandMaster::CheckCollectionCards(collection(), _myCards)) {
		cerr << "Internal Error: " << *this 
			<< " NOT using Valid Strategy!" << endl;
		assert(false);	
	}
}

ostream &operator<<(ostream &os, const CprPlayer& player) {
	cout << player.getId();
	return os;
}
