#pragma once
#include <cstddef>

class CharViewer
{
private:
	const char * start;
	std::size_t length;

public:
	/*
	CharViewer(const char * string, std::size_t offset, std::size_t length)
	{
		this->start = string + offset;
		this->length = length;
	}

	char operator[] (char offset)
	{
		return start[offset];
	}

	CharViewer substr(std::size_t pos = 0, std::size_t count = 0) const
	{
		return CharViewer(Start, pos, count);
	}
	class Iterator
	{
	public:
		friend class CharViewer;

	private:
		const char * start;
		std::size_t length;
		std::size_t current;

	private:
		Iterator(const CharViewer & charViewer, bool end)
		: start(charViewer.start), length(charViewer.length), current(end ? length : 0)
		{
		}

	public:
		const char & operator *(void) const
		{
			if(this->current == this->length)
				return '\0';
			return this->start[this->current];
		}

		Iterator & operator ++(void)
		{
			if(this->current < this->length)
			++this->current;
			return *this;
		}

		bool operator ==(const Iterator & other)
		{
			return (this->start == other.start)
			&& (this->length == other.length)
			&& (this->current == other.current);
		}

		bool operator !=(const Iterator & other)
		{
			return (this->start != other.start)
			|| (this->length != other.length)
			|| (this->current != other.current);
		}
	};	

	Iterator begin(void) const
	{
		return Iterator(*this, false);
	}

	Iterator end(void) const
	{
		return Iterator(*this, true);
	}
	*/
};
 