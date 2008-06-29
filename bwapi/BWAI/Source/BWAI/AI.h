#pragma once

#include <list>
#include <map>

#include <BWAPI/Game.h>
#include <BWAPI/ReservedResources.h>
#include <BW/UnitType.h>

namespace Util { class Logger; }

namespace PathFinding { class Utilities; }

namespace BWAI { class Unit; }
namespace BWAI { class TaskGatherGas; }
namespace BWAI { class TaskGather; }
namespace BWAI { class TaskBuild; }
namespace BWAI { class TaskInvent; }
namespace BWAI { class TaskUpgrade; }
namespace BWAI { class TaskFight; }
namespace BWAI { class TaskTrain; }
namespace BWAI { class Expansion; }
namespace BWAI { class MapInfo; }
namespace BWAI { class MapStartingPosition; }
namespace BWAI { class BuildingPositionSet; }
namespace BWAI { class BuildingPosition; }

namespace BuildOrder { class Root; }
namespace BuildOrder { class Command; }
namespace BuildOrder { class Branch; }

namespace BWAPI { class Player; }
namespace BWAPI { class UnitPrototype; }
namespace BWAPI { class Map; }

/** 
 * Set of classes providing ai tools.
 */
namespace BWAI
{
  /**
   * Singleton - root ai class maintaining all the stuff, it's only instance
   * should be the one defined in globals. 
   *
   * There are good reasons that the class is constructed dynamically, the main
   * is that non-dynamical classes have not defined order of constructor (c++
   * definition), so this class is constructated manually justa after the 
   * #BWAPI#Game is constructed and it uses it's content (configuration, logs)
   */
  class AI
  {
    public :
      AI();
      ~AI();
      /** Updates next/first pointers */
      void update();
      /** Call in the start of the game */
      void onStart(BWAPI::Player* player, BWAPI::Player* opponent);
      void onEnd();
      void onFrame();
      void onCancelTrain();
      void onRemoveUnit(BW::Unit* unit);
      bool onSendText(const char* text);

      std::list<Expansion*> expansions;
      Unit* getUnit(int index);
      static Unit* optimizeMineralFor;
      bool expansionsSaturated;
      Unit* getFirst();
      Util::Logger* log;
      Unit* freeBuilder(BW::Position position);

      std::list<TaskGatherGas*> activeRefineries;      
      std::list<TaskGather*> activeMinerals;
      std::list<TaskBuild*> plannedBuildings;
      std::list<TaskInvent*> plannedInvents;
      std::list<TaskUpgrade*> plannedUpgrades;
      std::list<TaskTrain*> plannedUnits;
      std::list<TaskFight*> fightGroups;
      BuildOrder::Root *root;
      std::list<BuildOrder::Command*>::iterator actualPosition;
      BuildOrder::Branch* actualBranch;
      
      std::map<std::string, BW::UnitType> unitNameToType;
      BWAPI::Player* player;
      BWAPI::Player* opponent;
      BuildingPosition* getFreeBuildingSpot(std::string spotName, Unit*& builderToUse);
      /**
       * Gets set of building positions (wrapped by the BuildingPosition class)
       * with the specified id. The operation speed should be log(count of
       * places) as the stl doesn't support hash, but whatever.
       * @param name of the building-place-set identification - it is the same
       *        as the name attribute in <building> tak in map xml file.
       * @returns BuildingPosition set with he specified name if present, @c
       *          NULL otherwise.
       */
      BuildingPositionSet* getPositionsCalled(const std::string& place);
      BWAPI::ReservedResources reserved;
      /** Currently opened map, NULL if no map is opened. */
      BWAPI::Map* map;
      PathFinding::Utilities *pathFinding;
      MapStartingPosition* startingPosition;      
      u16 mineralGatherers;
   private :
      Unit* units[BW::UNIT_ARRAY_MAX_LENGTH];
      BWAPI::UnitPrototype* worker;
      Unit* first;
      Util::Logger* deadLog;      
      MapInfo *mapInfo;
            
      void startNewExpansion(Unit *gatherCenter);
      void rebalanceMiners();
      void checkAssignedWorkers();
      void checkNewExpansions();
      void refreshSelectionStates(BW::Unit** selected);
      /**
       * If some building finished production, it will start the same unit again
       * @returns something happened (so reselect is needed)
       */
      void performAutoBuild();
      void getIdleWorkers(std::list<Unit*> &workers);
      void checkWorkersNeed();
      void assignIdleWorkersToMinerals(std::list<Unit*>& idleWorkers);
      int countOfTerranProductionBuildings();
      void checkSupplyNeed();
      /** @todo investigate and use the nextSupply provider here. */
      s32 plannedTerranSupplyGain();
      void executeTasks();
      TaskGather* bestFor(Unit* gatherer);
      void removeExpansion(Expansion* expansion);
      void unsaturateGather();
      void removeGatherGasTask(Unit* refinery);
      /**
       * Compares two mineral patches suitability for the given worker.
       * These things are taking into considaration:
       * -# Number of workers already assigned to the mineral patch.
       * -# Distance from the gatherer to the gatherCenter
       * -# Distance from the gatherCenter to mineral patch.
       * @param task1 TaskGather assigned to the first mineral patch
       * @param task2 TaskGather assigned to the second mineral patch
       * @param optimiseFor Define what worker is it regarded to (so the distance can can be taken in to
       *        account), if NULL conditions that needs to know the gatherer position won't be used.
       * @returns @c true if the fist mineral patch is better, @c false otherwise. 
       */
      bool betterMinralPatch(BWAI::TaskGather* task1, BWAI::TaskGather* task2, Unit* optimiseFor = NULL);
      /** Compares two workers suitability to be freed from it's task to do something else. */
      bool betterWorkerToFree(Unit* worker1, Unit* worker2, const BW::Position& buildingPosition);
      Unit* temp;
      
      bool cycle;
      BW::Position cyclePosition;
      float cycleAngle;
  };
}
