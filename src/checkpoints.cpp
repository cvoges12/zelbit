// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
typedef std::map<int, uint256> MapCheckpoints;

struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

//
// What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
//
static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of // Yo dawg, this is the secret. Checkpoint 0 hash == Genesis block hash.
        ( 0,  uint256("0xd494b733e6351d68a0e53bbebd76655e8941214dd77b516c2d0fd663e52f181c"))
        ( 48, uint256("0x721caf3934b1af95138092b40b9b6b3408a2eb38bca341c63180950f04e07c2f"))
        ( 70, uint256("0x6171cd10e6e1f4a475938ee5a73f9de608b09a16785e3898f6fe849d6236a2b9"))
        ;
static const CCheckpointData data = {
    &mapCheckpoints,
    1420564268, // * UNIX timestamp of last checkpoint block
    71, // * total number of transactions between genesis and last checkpoint
    // (the tx=... number in the SetBestChain debug.log lines)
    480.0 // * estimated number of transactions per day after checkpoint
};

bool CheckBlock(int nHeight, const uint256& hash)
{
    if (fTestNet) return true; // Testnet has no checkpoints

    MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
    if (i == mapCheckpoints.end()) return true;
    return hash == i->second;
}

int GetTotalBlocksEstimate()
{
    if (fTestNet) return 0;
    return mapCheckpoints.rbegin()->first;
}

CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
{
    if (fTestNet) return NULL;

    BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
    {
        const uint256& hash = i.second;
        std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
        if (t != mapBlockIndex.end())
            return t->second;
    }
    return NULL;
}
}
