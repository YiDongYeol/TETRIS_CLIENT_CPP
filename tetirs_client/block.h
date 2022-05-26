#pragma once
#include "base.h"


class block {
private:
	int shape[4][4];
	int current_dir;
public:
	block(int shape[4][4]);
	virtual void rotate(int direction);
	virtual void shaping() = 0;
	void setSize(int shape[4][4]);
	void setDirInit() { current_dir = 1; }
	int getCurrent_dir() const { return current_dir; }
	int getShape(int x, int y) const { return shape[x][y]; }
};

class _long : public block {
public:
	_long();
	virtual void shaping();
};
class _hand : public block {
public:
	_hand();
	virtual void shaping();
};
class _ltwist : public block {
public:
	_ltwist();
	virtual void shaping();
};
class _rtwist : public block {
public:
	_rtwist();
	virtual void shaping();
};
class _lgun : public block {
public:
	_lgun();
	virtual void shaping();
};
class _rgun : public block {
public:
	_rgun();
	virtual void shaping();
};
class _square :public block {
public:
	_square();
	virtual void shaping();
};