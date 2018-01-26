#include "MineBlockData.h"
#include <random>
#include <iostream>

CMineBlockData::CMineBlockData(size_t _row, size_t _col, size_t _bombNum)
{
	m_nRow = _row;
	m_nCol = _col;
	SetTotalBombNum(_bombNum);
}

CMineBlockData::~CMineBlockData()
{
}

void CMineBlockData::Resize(size_t _row, size_t _col, size_t _bombNum)
{
	m_nRow = _row;
	m_nCol = _col;
	SetTotalBombNum(_bombNum);
	// rearrange bomb
}

inline size_t CMineBlockData::GetRowNum() const
{
	return m_nRow;
}

inline size_t CMineBlockData::GetColNum() const
{
	return m_nCol;
}

void CMineBlockData::SetTotalBombNum(size_t _bombNum)
{
	m_nTotalBombs = _bombNum;
	m_nBombsRemain = _bombNum;
}

inline size_t CMineBlockData::GetRemainBombNum() const
{
	return m_nBombsRemain;
}


bool CMineBlockData::IsBomb(const size_t x, const size_t y) const
{
	if (CheckOutOfSize(x, y))
	{
		return m_data[x*m_nRow + y].isBomb;
	}
	return false;
}

bool CMineBlockData::IsClicked(const size_t x, const size_t y) const
{
	if (CheckOutOfSize(x, y))
	{
		return m_data[x*m_nRow + y].isClicked;
	}
	return false;
}

bool CMineBlockData::ClickAt(const size_t x, const size_t y)
{
	if (CheckOutOfSize(x, y))
	{
		const size_t idx = CalcIndex(x, y);
		if (!m_data[idx].isClicked)
		{
			m_data[idx].isClicked = true;
		}
		return !m_data[x*m_nRow + y].isBomb;
	}
	return false;
}

void CMineBlockData::SetFlag(const const size_t x, const const size_t y, const Flag _flag)
{
	if (CheckOutOfSize(x, y))
	{
		const size_t idx = CalcIndex(x, y);
		if (!m_data[idx].isClicked)
		{
			m_data[CalcIndex(x, y)].flag = _flag;
		}
	}
}

Flag CMineBlockData::GetFlag(const size_t x, const size_t y) const
{
	if (CheckOutOfSize(x, y))
	{
		return m_data[CalcIndex(x, y)].flag;
	}
	return Flag::EmFlgNormal;
}

bool CMineBlockData::CheckOutOfSize(const size_t x, const size_t y) const
{
	if (0 < x && x < m_nRow
		&& 0 < y && y < m_nCol)
	{
		return true;
	}
	// may throw exception
	return false;
}

inline size_t CMineBlockData::CalcIndex(const size_t x, const size_t y) const
{
	return x * m_nRow + y;
}

void CMineBlockData::RearrangeBomb()
{
	// reset cells
	for (size_t i = 0; i < m_data.size(); ++i)
	{
		m_data[i].flag = Flag::EmFlgNormal;
		m_data[i].isClicked = false;
		m_data[i].isBomb = i < m_nTotalBombs;
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(m_data.begin(), m_data.end(), g);
}
