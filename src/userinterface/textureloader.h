#pragma once

class TextureLoader
{
public:
	using SharedPointer = std::shared_ptr<vita2d_texture>;

private:
	SharedPointer MakeSharedPointer(vita2d_texture * texture)
	{
		return std::shared_ptr<vita2d_texture>(texture, vita2d_free_texture);
	}

public:
	SharedPointer LoadFromFile(const char * url)
	{
		vita2d_texture * texture = nullptr;

		texture = vita2d_load_PNG_file(url);
		if(texture != nullptr)
			return this->MakeSharedPointer(texture);
		
		texture = vita2d_load_JPEG_file(url);
		if(texture != nullptr)
			return this->MakeSharedPointer(texture);
		
		return SharedPointer(nullptr);
	}
};

class TextureCache
{
public:
	using Key = std::string;
	using SharedPointer = std::shared_ptr<vita2d_texture>;
	
private:
	std::map<const Key, SharedPointer> cache;
	TextureLoader textureLoader;

private:
	SharedPointer MakeSharedPointer(vita2d_texture * texture)
	{
		return std::shared_ptr<vita2d_texture>(texture, vita2d_free_texture);
	}
	
public:
	bool IsLoaded(const Key & url)
	{
		return (this->cache.find(url) != end(this->cache));
	}

	SharedPointer GetOrLoad(const Key & url)
	{
		auto iterator = this->cache.find(url);
		if(iterator != end(this->cache))
			return iterator->second;
		
		auto texture = this->textureLoader.LoadFromFile(url.c_str());		
		auto pair = this->cache.insert(std::make_pair(url, texture));

		if(pair.second)
			return pair.first->second;
		return SharedPointer(nullptr);
	}
	
	void Purge(void)
	{
		auto iterator = begin(this->cache);
		while(iterator != end(this->cache))
			if(iterator->second.use_count() < 2)
				iterator = this->cache.erase(iterator);
			else
				++iterator;
	}

	uint GetCount(void)
	{
		return(this->cache.size());
	}
};