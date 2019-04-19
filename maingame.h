#pragma once
class maingame
{
private:

public:
	maingame();
	~maingame();

	void Init();
	void Update();
	void Render();
	void Release();

	void ResetDevice();
	void LostDevice();
};

