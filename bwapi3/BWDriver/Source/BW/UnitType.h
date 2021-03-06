#pragma once

#include <string>
#include <map>

#include <Util/Bitmask.h>
#include <Util/Types.h>

#include "RaceID.h"
#include "UnitPrototypeFlags.h"
#include "GroupFlags.h"
#include "UnitID.h"
#include "TechID.h"
#include "UpgradeID.h"
#include "WeaponID.h"
#include "Offsets.h"
#include "UnitSizeType.h"


namespace BW
{
  /**
  * Definition of unit prototype, it's possible types are listed in #BW#UnitID.
  * The only data this class holds is the enumeration of type u16, so it can be used directly
  * in the mapping of #BW#Unit
  *
  * Use This class instance instead of the #BW#UnitID enumeration value as most as possible
  * alghough they are the same thing practicly, but the enumeration doesn't have all these
  * help functions, note that as there is == nad != operator and conversion constructor, so
  * the enumeration and this class can be compared/assigned freely.
  *
  */
  class UnitType
  {
    public :
      UnitType(); /**< Default constructor orderId will be BW::OrderID::None. */
      UnitType(const u16& id); /**< Conversion constructor */
      bool operator == (const u16& id) const;
      bool operator != (const u16& id) const;
      bool operator == (const UnitType& type) const;
      bool operator  < (const UnitType& type) const;

      u16         getID() const;
      const char* getName() const;
      const char* getSubLabel() const;
      u8          getRace() const;

      std::pair<BW::UnitType, int>         whatBuilds() const;
      const std::map< BW::UnitType, int >& requiredUnits() const;
      u8                                   requiredTech() const;
      u8                                   armorUpgrade() const;

      s32                  maxHitPoints() const;
      s16                  maxShields() const;
      u8                   maxEnergy() const;
      u8                   armor() const;

      u16                  mineralPrice() const;
      u16                  gasPrice() const;
      u16                  buildTime() const;

      u8                   supplyRequired() const;
      u8                   supplyProvided() const;
      u8                   spaceRequired() const;
      u8                   spaceProvided() const;
      u16                  buildScore() const;
      u16                  destroyScore() const;

      u8                   size() const;
      u16                  tileWidth() const;
      u16                  tileHeight() const;
      u16                  dimensionLeft() const;
      u16                  dimensionUp() const;
      u16                  dimensionRight() const;
      u16                  dimensionDown() const;

      u8                   seekRange() const;
      u8                   sightRange() const;
      u8                   groundWeapon() const;
      u8                   maxGroundHits() const;
      u8                   airWeapon() const;
      u8                   maxAirHits() const;

      u32                  topSpeed() const;
      u16                  acceleration() const;
      u32                  haltDistance() const;
      u8                   turnRadius() const;

      bool                 canProduce() const;
      bool                 canAttack() const;
      bool                 canMove() const; /**< I use some internal heuristic that every unit from [men]  group
                                            * can move, @todo verify (or load some value specially for that)
                                            * Note that there will have to be special canMove function for
                                            * BWAPI::Unit that will take unit instance specific things
                                            * like Not borrowed, not statised, not mealstormed, not under construction.
                                            */
      bool                 isFlyer() const;
      bool                 regeneratesHP() const;
      bool                 isSpellcaster() const;
      bool                 hasPermanentCloak() const;
      bool                 isInvincible() const;
      bool                 isOrganic() const;
      bool                 isMechanical() const;
      bool                 isRobotic() const;
      bool                 isDetector() const;
      bool                 isResourceContainer() const;
      bool                 isResourceDepot() const;
      bool                 isRefinery() const;
      bool                 isWorker() const;
      bool                 requiresPsi() const;
      bool                 requiresCreep() const;
      bool                 isTwoUnitsInOneEgg() const;
      bool                 isBurrowable() const;
      bool                 isCloakable() const;
      bool                 isBuilding() const;
      bool                 isAddon() const;
      bool                 isFlyingBuilding() const;
      bool                 isNeutral() const;

      u8                   graphics() const;
      bool                 isNeutralAccesories() const;
      bool                 isZerg() const;
      bool                 isTerran() const;
      bool                 isProtoss() const;
      bool                 isValid() const;
      u16                  id;
      static void initialize();
    private :
      Util::BitMask<u32> getFlags() const;
      Util::BitMask<u8>  getGroupFlags() const;
  };
};
