// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        pchMessageStart[0] = 0x38;
        pchMessageStart[1] = 0xaf;
        pchMessageStart[2] = 0xf5;
        pchMessageStart[3] = 0xe3;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 5858;
        nRPCPort = 5959;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //genesis.nTime = 1556755200
        //genesis.nNonce = 1064968
        //genesis.nVersion = 1
        //genesis.GetHash = 000008396359341b01d05e712bdd210862d4ff79ce4008a6e3daf12c8879bb15
        //genesis.hashMerkleRoot = dd104b65fa371204b0e0901700074360bcd5039721a83170b097da114d3043cf



        const char* pszTimestamp = "Aztec Warriors - Solar Warriors! We will revive the Aztec civilization!";
        CTransaction txNew;
        txNew.nTime = 1556755200;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1556755200;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1064968;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000008396359341b01d05e712bdd210862d4ff79ce4008a6e3daf12c8879bb15"));
        assert(genesis.hashMerkleRoot == uint256("0xdd104b65fa371204b0e0901700074360bcd5039721a83170b097da114d3043cf"));

        vSeeds.push_back(CDNSSeedData("aztecscoin.com", "aztecscoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(23);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(81);
        base58Prefixes[SECRET_KEY] =     list_of(151);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        //genesis.nTime = 1556755200
        //genesis.nNonce = 132122
        //genesis.nVersion = 1
        //genesis.hashMerkleRoot = dd104b65fa371204b0e0901700074360bcd5039721a83170b097da114d3043cf
        //genesis.GetHash = 000001acd5422d56cf6fc769858aae4cbcc5036dd99600bfb83b8e48038ca6e7

        pchMessageStart[0] = 0xad;
        pchMessageStart[1] = 0xf4;
        pchMessageStart[2] = 0xd0;
        pchMessageStart[3] = 0xac;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("");
        nDefaultPort = 15858;
        nRPCPort = 15959;
        strDataDir = "testnet";
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 132122;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000001acd5422d56cf6fc769858aae4cbcc5036dd99600bfb83b8e48038ca6e7"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;
// Regression test
//
//genesis.nTime = 1556755200
//genesis.nNonce = 0
//genesis.nVersion = 1
//genesis.hashMerkleRoot = dd104b65fa371204b0e0901700074360bcd5039721a83170b097da114d3043cf
//genesis.GetHash = 3a998667bd6c8435bfdcb731d6485eef807da031e2a34c47bae13a51634f7e89

class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xaf;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xcd;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1556755200;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 10444;
        strDataDir = "regtest";
        assert(hashGenesisBlock == uint256("0x3a998667bd6c8435bfdcb731d6485eef807da031e2a34c47bae13a51634f7e89"));
        vSeeds.clear();
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
