#include <iostream>
#include "mt.h"
#include "lcrng.h"
#include <math.h>
#include <string_view>
#include <array>
#include <regex>

using namespace std;

#define MAX_GREAT_MARSH (32)
#define DP_PRE_DEX (12)
#define DP_POST_DEX (14)
#define Pt_PRE_DEX (8)
#define Pt_POST_DEX (15)

static constexpr array<short, 4> greatMarshEncountersLimit{DP_PRE_DEX, DP_POST_DEX, Pt_PRE_DEX, Pt_POST_DEX};

short sanitizeGameVersionInput() {
    string gameVersion;
    const regex gameVersionRegex("^(dp|DP|Dp|dP|pt|PT|Pt|pT)$");

    while ((cout << "Game version? (dp/pt) ") && (!(cin >> gameVersion) || !regex_match(gameVersion, gameVersionRegex))) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    transform(gameVersion.begin(), gameVersion.end(), gameVersion.begin(), ::toupper);

    return gameVersion == "DP" ? 0 : 1;
}

bool sanitizeYesNoInput(const string output) {
    string yesNoAnswer;
    const regex yesNoRegex("^[nyNY]$");

    while ((cout << output) && (!(cin >> yesNoAnswer) || !regex_match(yesNoAnswer, yesNoRegex))) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return toupper(yesNoAnswer[0]) == 'Y';
}

void printEncounters(const short index) {
    static constexpr array<string_view, DP_PRE_DEX> greatMarshEncountersDPPreNationalDex{
        "Golduck", "Marill", "Wooper", "Quagsire", "Azurill", "Roselia", "Staravia", "Bidoof", "Bibarel", "Skorupi", "Croagunk",
        "Carnivine" };

    static constexpr array<string_view, DP_POST_DEX> greatMarshEncountersDPPostNationalDex{
        "Paras", "Golduck", "Exeggcute", "Kangaskhan", "Yanma", "Shroomish", "Roselia", "Gulpin", "Staravia", "Skorupi", "Drapion",
        "Croagunk", "Toxicroak", "Carnivine" };

    static constexpr array<string_view, Pt_PRE_DEX> greatMarshEncountersPtPreNationalDex{
        "Tangela", "Yanma", "Wooper", "Quagsire", "Tropius", "Skorupi", "Croagunk", "Carnivine" };

    static constexpr array<string_view, Pt_POST_DEX> greatMarshEncountersPtPostNationalDex{
        "Paras", "Exeggcute", "Tangela", "Kangaskhan", "Yanma", "Quagsire", "Shroomish", "Gulpin", "Kecleon", "Tropius", "Skorupi",
        "Drapion", "Croagunk", "Toxicroak", "Carnivine" };

    static constexpr array<const string_view*, 4> pokemonNames{ greatMarshEncountersDPPreNationalDex.data(), greatMarshEncountersDPPostNationalDex.data(),
                                                                greatMarshEncountersPtPreNationalDex.data(), greatMarshEncountersPtPostNationalDex.data() };

    cout << "\n\nSwarm encounters:\n\n";

    for (short i = 0; i < greatMarshEncountersLimit[index]; i++) {
        cout << i + 1 << " " << pokemonNames[index][i] << "\n";
    }

    cout << "\n\n";
}

template <typename T>
void sanitizeInput(const string output, T &value, const T lowLimit, const T highLimit) {
    while ((cout << output) && (!(cin >> value) || (value < lowLimit || value > highLimit))) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

uint8_t getAreaDailyEncounterIndex(const uint32_t seed, const short areaID) {
    return (seed >> (5 * areaID)) & 0x1F;
}

void printAreaEnocunters(short* encounterSpecies, const short index, const uint32_t seed) {
    static constexpr array<string_view, MAX_GREAT_MARSH> greatMarshEncounterDPPreNationalDexTable{
        "Croagunk", "Skorupi", "Carnivine", "Croagunk", "Skorupi", "Carnivine", "Golduck", "Croagunk", "Skorupi", "Carnivine",
        "Roselia", "Staravia", "Marill", "Azurill", "Wooper", "Golduck", "Staravia", "Croagunk", "Skorupi", "Carnivine", "Quagsire",
        "Bidoof", "Bibarel", "Wooper", "Azurill", "Roselia", "Staravia", "Croagunk", "Skorupi", "Carnivine", "Roselia", "Golduck" };

    static constexpr array<string_view, MAX_GREAT_MARSH> greatMarshEncounterDPPostNationalDexTable{
        "Croagunk", "Skorupi", "Carnivine", "Croagunk", "Skorupi", "Carnivine", "Golduck", "Croagunk", "Skorupi", "Carnivine",
        "Roselia", "Staravia", "Toxicroak", "Drapion", "Exeggcute", "Golduck", "Staravia", "Croagunk", "Skorupi", "Carnivine",
        "Yanma", "Shroomish", "Paras", "Kangaskhan", "Gulpin", "Roselia", "Staravia", "Croagunk", "Skorupi", "Carnivine",
        "Roselia", "Golduck" };

    static constexpr array<string_view, MAX_GREAT_MARSH> greatMarshEncounterPtPreNationalDexTable{
        "Wooper", "Wooper", "Wooper", "Carnivine", "Skorupi", "Croagunk", "Quagsire", "Wooper", "Skorupi", "Croagunk",
        "Quagsire", "Wooper", "Wooper", "Wooper", "Wooper", "Wooper", "Skorupi", "Croagunk", "Skorupi", "Carnivine",
        "Yanma", "Wooper", "Wooper", "Wooper", "Wooper", "Tropius", "Wooper", "Wooper", "Skorupi", "Carnivine", "Croagunk",
        "Tangela" };

    static constexpr array<string_view, MAX_GREAT_MARSH> greatMarshEncounterPtPostNationalDexTable{
        "Toxicroak", "Kecleon", "Kecleon", "Carnivine", "Skorupi", "Croagunk", "Quagsire", "Drapion", "Skorupi", "Croagunk",
        "Quagsire", "Kangaskhan", "Paras", "Drapion", "Exeggcute", "Exeggcute", "Skorupi", "Croagunk", "Skorupi", "Carnivine",
        "Yanma", "Shroomish", "Paras", "Kangaskhan", "Gulpin", "Tropius", "Gulpin", "Shroomish", "Skorupi", "Carnivine", "Croagunk",
        "Tangela" };

    static constexpr array<const string_view*, 4> pokemonDexNamesTable{ greatMarshEncounterDPPreNationalDexTable.data(), greatMarshEncounterDPPostNationalDexTable.data(),
                                                                        greatMarshEncounterPtPreNationalDexTable.data(), greatMarshEncounterPtPostNationalDexTable.data() };
    cout << "\n\n";

    for (short areaID = 0; areaID < 6; areaID++) {
        if (encounterSpecies[areaID]) {
            cout << "Area " << areaID + 1 << " - " << pokemonDexNamesTable[index][getAreaDailyEncounterIndex(seed, areaID)] << "\n";
        }
    }
}

bool isWantedEncounterCheck(const uint32_t seed, short* encounterDexIndexes, const short encounterDexIndexesNumber, const short index) {
    short encounterSpecies[6] = {0, 0, 0, 0, 0, 0};

    static constexpr array<short, MAX_GREAT_MARSH> greatMarshEncounteDPPreNationalDexIndexTable{
        453, 451, 455, 453, 451, 455, 55, 453, 451, 455, 315, 397, 183, 298, 194, 55, 397, 453, 451, 455, 195, 399, 400, 194, 298,
        315, 397, 453, 451, 455, 315, 55 };

    static constexpr array<short, MAX_GREAT_MARSH> greatMarshEncounterDPPostNationalDexIndexTable{
        453, 451, 455, 453, 451, 455, 55, 453, 451, 455, 315, 397, 454, 452, 102, 55, 397, 453, 451, 455, 193, 285, 46, 115, 316,
        315, 397, 453, 451, 455, 315, 55 };

    static constexpr array<short, MAX_GREAT_MARSH> greatMarshEncounterPtPreNationalDexIndexTable{
        194, 194, 194, 455, 451, 453, 195, 194, 451, 453, 195, 194, 194, 194, 194, 194, 451, 453, 451, 455, 193, 194, 194, 194, 194,
        357, 194, 194, 451, 455, 453, 114 };

    static constexpr array<short, MAX_GREAT_MARSH> greatMarshEncounterPtPostNationalDexIndexTable{
        454, 352, 352, 455, 451, 453, 195, 452, 451, 453, 195, 115, 46, 452, 102, 102, 451, 453, 451, 455, 193, 285, 46, 115, 316,
        357, 316, 285, 451, 455, 453, 114 };

    static constexpr array<const short*, 4> pokemonDexNumbersTable{ greatMarshEncounteDPPreNationalDexIndexTable.data(), greatMarshEncounterDPPostNationalDexIndexTable.data(),
                                                                    greatMarshEncounterPtPreNationalDexIndexTable.data(), greatMarshEncounterPtPostNationalDexIndexTable.data() };

    for (short i = 0; i < encounterDexIndexesNumber; i++) {
        bool foundFlag = false;

        for (short areaID = 0; areaID < 6; areaID++) {
            if (!encounterSpecies[areaID] && pokemonDexNumbersTable[index][getAreaDailyEncounterIndex(seed, areaID)] == encounterDexIndexes[i]) {
                encounterSpecies[areaID] = encounterDexIndexes[i];
                foundFlag = true;
                break;
            }
        }

        if (!foundFlag) {
            return false;
        }
    }

    printAreaEnocunters(encounterSpecies, index, seed);

    return true;
}

void findEncounterSeed(const short index) {
    short wantedEncountersNumber, encounter, minDelay, hour, minMTAdvances;
    const short maxDelay = 10000;

    sanitizeInput<short>("Insert how many encounters you are looking for (1-6): ", wantedEncountersNumber, 1, 6);
    short *wantedEncounterDexIndexes = new short[wantedEncountersNumber];

    static constexpr array<short, DP_PRE_DEX> greatMarshEncounteDPPreNationalDexNumbers{
        55, 183, 194, 195, 298, 315, 397, 399, 400, 451, 453, 455 };

    static constexpr array<short, DP_POST_DEX> greatMarshEncounteDPPostNationalDexNumbers{
        46, 55, 102, 115, 193, 285, 315, 316, 397, 451, 452, 453, 454, 455 };

    static constexpr array<short, Pt_PRE_DEX> greatMarshEncountePtPreNationalDexNumbers{
        114, 193, 194, 195, 357, 451, 453, 455 };

    static constexpr array<short, Pt_POST_DEX> greatMarshEncountePtPostNationalDexNumbers{
        46, 102, 114, 115, 193, 195, 285, 316, 352, 357, 451, 452, 453, 454, 455 };

    static constexpr array<const short*, 4> pokemonDexNumbers{ greatMarshEncounteDPPreNationalDexNumbers.data(), greatMarshEncounteDPPostNationalDexNumbers.data(),
                                                               greatMarshEncountePtPreNationalDexNumbers.data(), greatMarshEncountePtPostNationalDexNumbers.data() };

    for (short i = 0; i < wantedEncountersNumber; i++) {
        sanitizeInput<short>("Insert the wanted encounter index number " + to_string(i + 1) + ": ", encounter, 1, greatMarshEncountersLimit[index]);
        wantedEncounterDexIndexes[i] = pokemonDexNumbers[index][encounter - 1];
    }

    sanitizeInput<short>("Insert the min delay: ", minDelay, 600, 9999);
    sanitizeInput<short>("Insert the min hours (0-23): ", hour, 0, 23);
    sanitizeInput<short>("Insert the needed MT advances: ", minMTAdvances, 0, 9999);

    for (short ab = 0; ab < 256; ab++) {
        for (short cd = hour; cd < 24; cd++) {
            for (short efgh = minDelay; efgh < maxDelay; efgh++) {
                const uint32_t seed = ((ab << 24) | (cd << 16)) + efgh;
                mt MT(seed);
                lcrng LCRNG(MT.advance(minMTAdvances));

                if (isWantedEncounterCheck(LCRNG.next(2), wantedEncounterDexIndexes, wantedEncountersNumber, index)) {
                    printf("\nTarget seed: %08X\n\n------------------------------------------------\n\n", seed);
                    return;
                }
            }
        }
    }

    cout << "\n\nNothing found\n\n------------------------------------------------\n\n";
}

int main() {
    while (true) {
        const short game = sanitizeGameVersionInput(), dexFlag = sanitizeYesNoInput("Did you obtain the National Pokédex? (y/n) ") ? game + 1 : game;
        const short tableIndex = game + dexFlag;
        printEncounters(tableIndex);
        findEncounterSeed(tableIndex);
    }
}