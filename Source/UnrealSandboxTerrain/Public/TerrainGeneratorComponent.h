// Copyright blackw 2015-2020

#pragma once

#include "EngineMinimal.h"
#include <unordered_map>
#include "TerrainGeneratorComponent.generated.h"

class ASandboxTerrainController;
class TVoxelData;


struct TVoxelIndex {
    int X = 0;
    int Y = 0;
    int Z = 0;
    
    bool operator==(const TVoxelIndex &other) const {
        return (X == other.X && Y == other.Y && Z == other.Z);
    }
};

namespace std {
    
    template <>
    struct hash<TVoxelIndex> {
        std::size_t operator()(const TVoxelIndex& k) const {
            using std::hash;
            
            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:
            
            return ((hash<int>()(k.X) ^ (hash<int>()(k.Y) << 1)) >> 1) ^ (hash<int>()(k.Z) << 1);
        }
    };
}

class TZoneHeightMapData {
    
private:
    
    int Size;
    
    float* HeightLevelArray;
    
public:
    
    TZoneHeightMapData(int size);
    
    ~TZoneHeightMapData();
    
    FORCEINLINE void SetHeightLevel(TVoxelIndex VoxelIndex, float HeightLevel);
    
    FORCEINLINE float GetDensity(TVoxelIndex VoxelIndex) const ;
};



/**
*
*/
UCLASS()
class UNREALSANDBOXTERRAIN_API UTerrainGeneratorComponent : public USceneComponent
{
	GENERATED_UCLASS_BODY()

public:


public:
	void GenerateVoxelTerrain(TVoxelData &VoxelData);

	float GroundLevelFunc(FVector v);

private:
    
    std::unordered_map<TVoxelIndex, std::string> ZoneHeightMapCollection;

	ASandboxTerrainController* GetTerrainController() {
		return (ASandboxTerrainController*)GetAttachmentRootActor();
	};
	
	float ClcDensityByGroundLevel(FVector v);

	float DensityFunc(const FVector& ZoneIndex, const FVector& LocalPos, const FVector& WorldPos);

	unsigned char MaterialFunc(const FVector& LocalPos, const FVector& WorldPos);
};
