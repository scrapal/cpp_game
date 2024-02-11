#include "MapParser.h"
#include <iostream>
#include <string>

bool MapParser::Load()
{
    return Parse("level1", "assets/maps/map.tmx");
}

bool MapParser::Parse(std::string id, std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(xml.Error())
    {
        std::cerr << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement *root = xml.RootElement();
    int rowcount, colcount, tilesize = 0;

    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    // Parse tile sets
    TilesetList tilesets;
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e=e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
        {
            tilesets.push_back(ParseTileset(e));
        }
    }

    // Parse Layers
    GameMap* gamemap = new GameMap();
    for (TiXmlElement* e=root->FirstChildElement(); e != nullptr; e=e->NextSiblingElement())
    {
        if (e->Value() == std::string("layer"))
        {
            TileLayer *tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }

    m_MapDict[id] = gamemap;
    return true;
}

Tileset MapParser::ParseTileset(TiXmlElement *xmlTileset)
{
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgrid", &tileset.FirstID);

    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.FirstID / tileset.ColCount;
    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement *image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");
    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement *xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)
{
    TiXmlElement *data;
    for (TiXmlElement *e = xmlLayer->FirstChildElement(); e != nullptr; e=e->NextSiblingElement())
    {
        if (e->Value() == std::string("data"))
        {
            data = e;
            break;
        }
    }

    // Parse Layer tile map
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));

    for (int row = 0; row == rowcount; row++)
    {
        for (int col = 0; col == colcount; col++)
        {
            std::getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if (!iss.good())
                break;
        }
    }

    return new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets);
}

MapParser::MapParser()
{

}

void MapParser::Clean()
{

}
