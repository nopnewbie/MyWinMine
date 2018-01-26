#pragma once
#include <vector>

enum Flag
{
	EmFlgNormal,
	EmFlgBomb,
	EmFlgUncertain
};

struct Cell
{
	Cell()
		: flag(Flag::EmFlgNormal)
		, isClicked(false)
		, isBomb(false)
	{ }

	Flag flag;
	bool isClicked;
	bool isBomb;
};

class CMineBlockData
{
public:
	CMineBlockData() = default;
	CMineBlockData(const size_t _row, const size_t _col, const size_t _bombNum);
	~CMineBlockData();

	void Resize(const size_t _row, const size_t _col, const size_t _bombNum);
	size_t GetRowNum() const;
	size_t GetColNum() const;
	size_t GetRemainBombNum() const;
	void SetTotalBombNum(const size_t _bombNum);

	bool IsBomb(const size_t x, const size_t y) const;
	bool IsClicked(const size_t x, const size_t y) const;
	bool ClickAt(const size_t x, const size_t y);
	void SetFlag(const size_t x, const size_t y, const Flag _flag);
	Flag GetFlag(const size_t x, const size_t y) const;
	void RearrangeBomb();

private:

	bool CheckOutOfSize(const size_t x, const size_t y) const;
	size_t CalcIndex(const size_t x, const size_t y) const;

	// size of block
	size_t m_nRow;
	size_t m_nCol;

	size_t m_nBombsRemain;
	size_t m_nTotalBombs;

	std::vector<Cell> m_data;
};

