// Copyright (c) 2019, Zpalmtree
//
// Please see the included LICENSE file for more information.

#pragma once

#include <functional>
#include <memory>

#include "ArgonVariants/Argon2Hash.h"
#include "Types/IHashingAlgorithm.h"
#include "Utilities/String.h"

namespace ArgonVariant
{
    enum Algorithm
    {
        Argon2SCR
    };

    /* Mapping from all the possible algorithm names under the sun to the
       internal algorithm enum. It is assumed that you will run algorithmNameToCanonical
       with this list to handle casing issues.

       The third parameter determines if we should display the algorithm
       name when listing available algorithms. */
    inline std::vector<std::tuple<std::string, Algorithm, bool>> algorithmNameMapping
    {
        
        /* SECURUS */
        { "scr",    		Argon2SCR, true  },
        { "securus",       	Argon2SCR, true  },
        
      
    };

    inline Algorithm algorithmNameToCanonical(const std::string &algorithmNameDirty)
    {
        std::string algorithmName = algorithmNameDirty;

        std::transform(algorithmName.begin(), algorithmName.end(), algorithmName.begin(), ::tolower);

        Utilities::trim(algorithmName);

        const auto it = std::find_if(algorithmNameMapping.begin(), algorithmNameMapping.end(),
        [&algorithmName](const auto algo)
        {
            return std::get<0>(algo) == algorithmName;
        });

        if (it == algorithmNameMapping.end())
        {
            throw std::runtime_error("Unknown algorithm name " + algorithmNameDirty + "!");
        }

        return std::get<1>(*it);
    }

    inline std::shared_ptr<Argon2Hash> getCPUMiningAlgorithm(std::string algorithm)
    {
        switch(algorithmNameToCanonical(algorithm))
        {
            case Argon2SCR:
            {
                return std::make_shared<Argon2Hash>(
                    256,
                    4,
                    1,
                    16,
                    Constants::ARGON2ID
                );
            }
            default:
            {
                throw std::runtime_error("Developer fucked up. Sorry!");
            }
        }
    }
}
