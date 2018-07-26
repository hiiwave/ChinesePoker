/****************************************************************************
FileName   [ CprStage.cpp ]
Synopsis   [ implement each phase in a single stage ]
****************************************************************************/

#include "CprStage.h"
#include "CprDealer.h"
#include "CprPlayer.h"
#include "CprHand.h"

CprStage::CprStage(PlayerList & players, int id)
	: _players(players), _stageId(id) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			_TrickCount[i][j] = 0;
		}
	}
}

CprStage::~CprStage() {
}

void CprStage::start() {
	cout << "== Stage " << _stageId << " start!" << endl;
	dealingPhase();
	strategyPhase();
	checkXianggongPhase();
	comparisonPhase();
	shootingPhase();
	printScores();
	cout << "== Stage " << _stageId << " end" << endl << endl;
	cout << endl;
}

void CprStage::dealingPhase() {
	for (CprPlayer *py : _players) {
		py->reset();
	}
	CprDealer dealer;
	dealer.deal(_players);
}

void CprStage::strategyPhase() {
	for (CprPlayer *py : _players) {
		py->strategy();
	}
}

void CprStage::checkXianggongPhase() {
	for (CprPlayer *py : _players) {
		if (!(py->getHand(0) <= py->getHand(1)) || !(py->getHand(1) <= py->getHand(2))) {
			(py->hand(0)).setXianggong();
			(py->hand(1)).setXianggong();
			(py->hand(2)).setXianggong();
		}
	}
}

void CprStage::comparisonPhase() {
	for (int hidx = 0; hidx < 3; ++hidx) {
		cout << "= Round " << hidx + 1 << ".." << endl;
		int tricks[4] = {};
		for (unsigned p = 0; p < _players.size() - 1; ++p) {
			CprPlayer *py = _players.at(p);
			for (unsigned q = p + 1; q < _players.size(); ++q) {
				CprPlayer *oppo = _players.at(q);
				if (py->hand(hidx) <= oppo->hand(hidx) && oppo->hand(hidx) <= py->hand(hidx)) {
				} else if (py->hand(hidx) <= oppo->hand(hidx)) {
					--tricks[p];
					++tricks[q];
					oppo->winOneTrick(py);
					_TrickCount[p][q] -= 1;
				} else if (oppo->hand(hidx) <= py->hand(hidx)) {
					++tricks[p];
					--tricks[q];
					py->winOneTrick(oppo);
					_TrickCount[p][q] += 1;
				} else {
					assert(false);
				}
			}
		}
		for (unsigned p = 0; p < _players.size(); ++p) {
			CprPlayer *py = _players.at(p);
			int a = (int)(py->getId()).length();
			py->printId(1);
			(py->getHand(hidx)).print(1);
			cout << " : ";
			int trick = tricks[p];
			if (trick >= 0)  cout << "+";
			cout << trick << endl;
		}
	}
}

void CprStage::shootingPhase() {
	cout << "= Check shooting.." << endl;
	for (unsigned p = 0; p < _players.size() - 1; ++p) {
		for (unsigned q = p; q < _players.size(); ++q) {
			CprPlayer *py = _players.at(p);
			CprPlayer *oppo = _players.at(q);
			if (_TrickCount[p][q] == 3) {
				py->gunShooting(oppo);
			} else if (_TrickCount[p][q] == -3) {
				oppo->gunShooting(py);
			}
		}
	}
}


static string h_placeFromScore(int score, const vector<int> &scores) {
	int place = 1;
	for (int s : scores) {
		if (s > score) {
			++place;
		}
	}
	switch (place) {
	case 1:
		return "1st";
	case 2:
		return "2nd";
	case 3:
		return "3rd";
	case 4:
		return "4th";
	default:
		return "ERR";
	}
}

void CprStage::printScores() const {
	cout << "== Stage " << _stageId << " scores.." << endl;
	vector<int> scores;
	for (const CprPlayer *py : _players) {
		scores.push_back(py->getScore());
	}
	for (const CprPlayer *py : _players) {
		py->printId(1);
		cout << setw(4) << py->getScore() << " ("
			<< h_placeFromScore(py->getScore(), scores) << ")" << endl;
	}
}

