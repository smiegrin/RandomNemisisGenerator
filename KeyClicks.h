#pragma once

class KeyClicks {
  bool* hit;
  bool* down;
  bool* up;
  int keyLength;

public:

  KeyClicks(int);
  ~KeyClicks();

	bool getHit(int keyNum) const;
	bool getDown(int keyNum) const;
	bool getUp(int keyNum) const;

  void hitKey(int keyNum);
  void upKey(int keyNum);
  void timeStep();
};
