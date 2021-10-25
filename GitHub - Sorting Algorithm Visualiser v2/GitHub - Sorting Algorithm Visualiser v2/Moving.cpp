
#include "Moving.h"

enum DIR {

	UP,
	RIGHT,
	DOWN,
	LEFT

};

struct Mover{

	NumberBox* lft;
	NumberBox* rght;

	int Lfb;
	int Lnb;
	int Ltb;

	int Rfb;
	int Rnb;
	int Rtb;

	int ctr;

	Mover(NumberBox* a, NumberBox* b) {

		lft = a->x() < b->x() ? a : b;
		rght = b->x() > a->x()  ? b : a;

		Lfb = lft->y() - lft->s();
		Lnb = rght->x();
		Ltb = rght->y();

		Rfb = rght->y() + rght->s();
		Rnb = lft->x();
		Rtb = lft->y();

		ctr = 0;
	}

};

Caller CALLING;

int STATIC_S = 0;

void nudge(NumberBox* a, DIR d, int delta, int border) {

	switch (d){

	case UP:
		a->position(a->x(), (max(a->y() - delta, border)));
		break;
	case RIGHT:
		a->position(min(a->x() + delta, border), a->y());
		break;
	case DOWN:
		a->position(a->x(), (min(a->y() + delta, border)));
		break;
	case LEFT:
		a->position(max(a->x() - delta, border), a->y());
		break;
	}


}

bool ft(NumberBox* l, NumberBox* r, int lb, int rb) {

	nudge(l, UP, DELTA, lb);
	nudge(r, DOWN, DELTA, rb);

	if (l->y() == lb)
		return true;	//end trasnform
	else
		return false;

}

bool nt(NumberBox* l, NumberBox* r, int lb, int rb) {

	nudge(l, RIGHT, DELTA, lb);
	nudge(r, LEFT, DELTA, rb);

	if (l->x() == lb)
		return true;	//end trasnform
	else
		return false;
}

bool tt(NumberBox* l, NumberBox* r, int lb, int rb) {

	nudge(l, DOWN, DELTA, lb);
	nudge(r, UP, DELTA, rb);

	if (l->y() == lb)
		return true;	//end trasnform
	else
		return false;
}

void SwpCb(void* v) {

	Mover* p = (Mover*)v;

	switch (p->ctr) {

	case 0:
		if (ft(p->lft, p->rght, p->Lfb, p->Rfb))
			p->ctr++;
		break;

	case 1:
		if (nt(p->lft, p->rght, p->Lnb, p->Rnb))
			p->ctr++;
		break;
	case 2:
		if (tt(p->lft, p->rght, p->Ltb, p->Rtb))
			p->ctr++;
		break;
	case 3: 
		p->lft->ol(FL_BLACK);
		p->rght->ol(FL_BLACK);
		CALLING.w->redraw();
		CALLING();
		delete p;
		return;
	}
	CALLING.w->redraw();

	Fl::repeat_timeout(RATE, SwpCb, p);

}

void CompCb(void* v) {

	auto p = (pair<NumberBox*, NumberBox*>*)v;

	p->first->ol(FL_BLACK);
	p->second->ol(FL_BLACK);

	delete p;

	CALLING();
	
}

void AnimateSwap(vector<NumberBox*>* nb, int i, int j) {

	Mover* pck = new Mover{ (*nb)[i], (*nb)[j] };
	(*nb)[i]->ol(SWP_C);
	(*nb)[j]->ol(SWP_C);

	Fl::add_timeout(0, SwpCb, pck);

	auto p = (*nb)[i];	//this is to actually swap position in the vector, not just their positions
	(*nb)[i] = (*nb)[j];
	(*nb)[j] = p;
}

void AnimateComp(vector<NumberBox*>* nb, int i, int j) {

	(*nb)[i]->ol(COMP_C);
	(*nb)[j]->ol(COMP_C);

	CALLING.w->redraw();
		
	pair<NumberBox*, NumberBox*>* p = new pair<NumberBox*, NumberBox*> { (*nb)[i], (*nb)[j] };
	
	Fl::add_timeout(COMP_T, CompCb, p);

}

void AnimateSeq(vector<NumberBox*>* nb, Fl_Double_Window* w, SoC* sc) {

	CALLING.nb = nb;
	CALLING.w = w;
	CALLING.sc = sc;

	if (STATIC_S == sc->size()) {
		
		STATIC_S = 0;
		CALLING.w->redraw();
		
		delete CALLING.nb;
		delete CALLING.sc;

		CALLING.nb = NULL;
		CALLING.sc = NULL;

		for (auto& p : *nb) {
			delete p;
			p = NULL;
		}
		
		return;
	}

	pair<pair<int, int>, bool> p = (*sc)[STATIC_S];
	
	STATIC_S++;

	if (p.first.first == p.first.second) {
		CALLING();
		return;
	}

	if (p.second == 0)
		AnimateSwap(nb, p.first.first, p.first.second);
		//CALLING();
	else
		AnimateComp(nb, p.first.first, p.first.second);

}

