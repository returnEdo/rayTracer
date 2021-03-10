#pragma once

#include "EscapeCodes.h"


class ProgressBar{

	private:

	int length;
	int roof;

	public:

	ProgressBar(int len, int r);
	~ProgressBar(void);

	void update(int val) const;
};
