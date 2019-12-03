#include "pch.h"
#include "Number.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Number::Number()
	:
	m_num(0)
{
}

Number::~Number()
{
}

void Number::Draw(DirectX::SpriteBatch * spriteBatch)
{
	int num = m_num;

	if (num >= 99)
	{
		num = 99;
	}

	int buf = 1;
	num /= 10;
	while (num > 0)
	{
		num /= 10;
		buf *= 10;
	}

	Vector2 pos = m_pos;
	num = m_num;

	if (m_num < 10)
	{
		Vector2 posBuf = pos;
		posBuf.x = pos.x;
		spriteBatch->Draw(m_texture[0], posBuf);
		posBuf.x = pos.x + 38;
		spriteBatch->Draw(m_texture[m_num], posBuf);
	}
	else
	{
		while (buf > 0)
		{
			int elem = (num % (buf * 10)) / buf;
			buf /= 10;
			spriteBatch->Draw(m_texture[elem], pos);
			pos.x += 38;
		}
	}
}

void Number::SetNum(int num)
{
	m_num = num;
}

void Number::SetPos(DirectX::SimpleMath::Vector2 pos)
{
	m_pos = pos;
}

void Number::SetTexture(int n, ID3D11ShaderResourceView* texture)
{
	m_texture[n] = texture;
}
