//
// Created by robcholz on 5/4/23.
//

#ifndef RUNCRAFT_SAVEHELPER_HPP
#define RUNCRAFT_SAVEHELPER_HPP

#include <boost/algorithm/string/find.hpp>
#include <bitsery/adapter/buffer.h>
#include <bitsery/adapter/stream.h>
#include <bitsery/bitsery.h>
#include <cmath>
#include "resource/FileHelper.hpp"
#include "world/chunk/Chunk.hpp"
#include "world/chunk/ChunkDataPacketAdapter.hpp"


class SaveHelper {
private:
	using String = std::string;
	using Buffer = std::vector<uint8_t>;
	String saveDirectory;

	FileHelper savesDirectoryHelper{"../external/saves"};
	std::unique_ptr<FileHelper> saveHelper, regionHelper, entitiesHelper, playerdataHelper;

protected:
	static String getRegionName(coordinate::ChunkPositionT chunkPos) { return "r.0." + std::to_string(chunkPos); }

	/**
	 * @Usage Create a new region file with the given name format r.0.[index]
	 * @param chunkPos The chunkPosition
	 */
	void createRegion(coordinate::ChunkPositionT chunkPos) {
		String filename = saveDirectory + "/region/" + getRegionName(chunkPos) + ".mca";
		std::fstream regionFile{filename, std::ios::binary | std::ios::trunc | std::ios::out};
		regionFile.close();
	}

	chunk::Chunk* loadRegion(const String &filename) {
		std::ofstream regionFile;
		regionFile.open(saveDirectory + "/region/" + filename + ".mca", std::ios::binary | std::ios::in);
		ChunkDataPacket chunk_data_packet;
		auto state = bitsery::quickDeserialization<bitsery::InputStreamAdapter>(regionFile, chunk_data_packet);
		// TODO where is the fuckin problem?
		chunk::adapter::ChunkDataPacketAdapter::decompress(&chunk_data_packet);
		std::cout << (state.first == bitsery::ReaderError::NoError && state.second);
		return nullptr;//chunk_data_input_adapter.getChunk();
	}

	void writeRegion(const String &filename, chunk::Chunk* chunk) {
		std::ofstream regionFile;
		regionFile.open(saveDirectory + "/region/" + filename + ".mca", std::ios::binary | std::ios::trunc | std::ios::out);
		bitsery::Serializer<bitsery::OutputBufferedStreamAdapter> serializer{regionFile};
		ChunkDataPacket chunk_data_packet;
		chunk::adapter::ChunkDataPacketAdapter::compress(chunk, &chunk_data_packet);
		serializer.object(chunk_data_packet);
		serializer.adapter().flush();
		regionFile.close();
	}


	void createSaveFolder(const String &saveName) {
		saveDirectory = savesDirectoryHelper.createSubFolder(saveName);
		FileHelper::createFolder(saveDirectory, "advancements"); //Stores the advancements and unlocked recipes of the players that have played on this level.
		FileHelper::createFolder(saveDirectory, "region"); //Contains region files for the Overworld.
		FileHelper::createFolder(saveDirectory, "entities"); //Contains entity files for the Overworld. These used to be part of region.
		FileHelper::createFolder(saveDirectory, "playerdata"); //Stores the individual states of the players that have played on this level.
		FileHelper::createFolder(saveDirectory, "stats"); //Stores the statistics of the players that have played on this level.
		FileHelper::createFile(saveDirectory, "level.dat"); //Stores global information about the level.
	}

	void loadSave() {}

public:
	enum class ModeType : uint8_t {
		READ,
		CREATE
	};

	explicit SaveHelper(const String &filename, ModeType mode) {
		if (mode == ModeType::CREATE)
			createSaveFolder(filename);
		if (mode == ModeType::READ)
			//loadSave(filename);
			saveHelper = std::make_unique<FileHelper>(saveDirectory);
		regionHelper = std::make_unique<FileHelper>(saveDirectory + "/region");
		entitiesHelper = std::make_unique<FileHelper>(saveDirectory + "/entities");
		playerdataHelper = std::make_unique<FileHelper>(saveDirectory + "/playerdata");
	}

	~SaveHelper() = default;

	void saveChunk(chunk::Chunk* chunk) {
		createRegion(chunk->getChunkPosition());
		writeRegion(getRegionName(chunk->getChunkPosition()), chunk);
	}

	chunk::Chunk* loadChunk(coordinate::ChunkPositionT chunkPos) {
		return loadRegion(getRegionName(chunkPos));
	}
};

#endif //RUNCRAFT_SAVEHELPER_HPP
