#include <iostream>
#include <format>
#include <string>
#include <stdlib.h>

enum BuildingType { EMPTY, HYDROELECTRIC_POWER_PLANT, WIND_POWER_PLANT, SOLAR_PANEL };

bool checkIfNumberOfGivenArgumentsMeetsTheRequirements(int numberOfGivenArguments, std::string& responseMessage);
bool checkIfGivenArgumentsMeetTheRequirements(int numberOfGivenArguments, char* givenArguments[], short& width, short& height, std::string& responseMessage);
bool parseAnArgument(char* givenArgument, short& referenceToParsingTarget, std::string& responseMessage);
void initializeTheConstructionPlane(BuildingType* constructionPlane, short width, short height, std::string& responseMessage);
bool placeABuilding(BuildingType* constructionPlane, short constructionPlaneWidth, short constructionPlaneHeight, BuildingType typeOfBuildingToPlace, short positionX, short positionY, short width, short height, std::string& responseMessage);
bool removeASpecificArea(BuildingType* constructionPlane, short constructionPlaneWidth, short constructionPlaneHeight, short positionX, short positionY, short width, short height, std::string& responseMessage);
bool checkIfAPositionIsWithinTheConstructionPlane(short constructionPlaneSizeInTheGivenDimension, short coordinate, std::string& responseMessage);
bool checkIfTheBuildingExceedsTheConstructionPlaneInOneDimension(short constructionPlaneSizeInTheGivenDimension, short coordinate, short buildingSizeInTheGivenDimension, std::string& responseMessage);
bool checkIfThereIsACollision(BuildingType* constructionPlane, short constructionPlaneWidth,short positionX, short positionY, short width, short height, std::string& responseMessage);
void displayTheConstructionPlane(BuildingType* constructionPlane, short width, short height);
std::string determineTheActualIdentifierOfABuldingTypeByIndex(short index);
void terminateTheProgram(void);

constexpr short MINIMUM_NUMBER_OF_REQUIRED_COMMAND_LINE_ARGUMENTS = 2;
constexpr short MAXIMUM_NUMBER_OF_REQUIRED_COMMAND_LINE_ARGUMENTS = 2;



int main(int argc, char* argv[])
{
    int exitReturnCodeOfMain = 0;
    std::string responseMessage = "";
    bool numberOfGivenArgumentsMeetsTheRequirements = checkIfNumberOfGivenArgumentsMeetsTheRequirements(argc, responseMessage);
    if (numberOfGivenArgumentsMeetsTheRequirements == true)
    {
        std::cout << responseMessage << std::endl;
        short width = 0;
        short height = 0;
        bool givenArgumentsMeetTheRequirements = checkIfGivenArgumentsMeetTheRequirements(argc, argv, width, height, responseMessage);
        if (givenArgumentsMeetTheRequirements == true)
        {
            std::cout << responseMessage << std::endl;
            BuildingType* constructionPlane = new BuildingType[height * width];
            initializeTheConstructionPlane(constructionPlane, width, height, responseMessage);
            std::cout << responseMessage << std::endl;
            displayTheConstructionPlane(constructionPlane, width, height);
            bool buildingPlacementResult = placeABuilding(constructionPlane, width, height, SOLAR_PANEL, 2, 2, 2, 2, responseMessage);
            if (buildingPlacementResult == true)
            {
                std::cout << responseMessage << std::endl;
            }
            else
            {
                std::cerr << responseMessage << std::endl;
            }
            buildingPlacementResult = placeABuilding(constructionPlane, width, height, SOLAR_PANEL, 2, 2, 2, 2, responseMessage);
            if (buildingPlacementResult == true)
            {
                std::cout << responseMessage << std::endl;
            }
            else
            {
                std::cerr << responseMessage << std::endl;
            }
            displayTheConstructionPlane(constructionPlane, width, height);
            buildingPlacementResult = placeABuilding(constructionPlane, width, height, WIND_POWER_PLANT, 1, 1, 3, 3, responseMessage);
            if (buildingPlacementResult == true)
            {
                std::cout << responseMessage << std::endl;
            }
            else
            {
                std::cerr << responseMessage << std::endl;
            }
            displayTheConstructionPlane(constructionPlane, width, height);
    
            bool areaIsRemocedSuccessfully = removeASpecificArea(constructionPlane, width, height, 1, 1, 1, 1, responseMessage);
            if (areaIsRemocedSuccessfully == true)
            {
                std::cout << responseMessage << std::endl;
            }
            else
            {
                std::cerr << responseMessage << std::endl;
            }
            displayTheConstructionPlane(constructionPlane, width, height);

            delete[] constructionPlane;
            terminateTheProgram();
        }
        else
        {
            std::cerr << responseMessage << std::endl;
            exitReturnCodeOfMain = 1;
        }
    }
    else
    {
        std::cerr << responseMessage << std::endl;
        exitReturnCodeOfMain = 1;
    }

    return exitReturnCodeOfMain;
}

bool checkIfNumberOfGivenArgumentsMeetsTheRequirements(int numberOfGivenArguments, std::string& responseMessage)
{
    bool resultOfRequirementCheckingProcess = false;
    short actualNumberOfGivenArguments = numberOfGivenArguments - 1;
    if (actualNumberOfGivenArguments >= MINIMUM_NUMBER_OF_REQUIRED_COMMAND_LINE_ARGUMENTS)
    {
        if (actualNumberOfGivenArguments > MAXIMUM_NUMBER_OF_REQUIRED_COMMAND_LINE_ARGUMENTS)
        {
            responseMessage = std::format("You provided {0} command line arguments, which is more than the required {1}.", actualNumberOfGivenArguments, MAXIMUM_NUMBER_OF_REQUIRED_COMMAND_LINE_ARGUMENTS);
        }
        else
        {
            responseMessage = std::format("You provided a correct number of command line arguments!");
            resultOfRequirementCheckingProcess = true;
        }
    }
    else
    {
        responseMessage = std::format("You provided {0} command line arguments, which is less than the required {1}.", actualNumberOfGivenArguments, MINIMUM_NUMBER_OF_REQUIRED_COMMAND_LINE_ARGUMENTS);
    }

    return resultOfRequirementCheckingProcess;
}

bool checkIfGivenArgumentsMeetTheRequirements(int numberOfGivenArguments, char* givenArguments[], short& width, short& height, std::string& responseMessage)
{
    //short acutalNumberOfGivenArguments = numberOfGivenArguments - 1;
    responseMessage = "";
    bool resultOfFirstParsingProcess = parseAnArgument(givenArguments[1], height, responseMessage);
    bool resultOfSecondParsingProcess = parseAnArgument(givenArguments[2], width, responseMessage);

    return resultOfFirstParsingProcess && resultOfSecondParsingProcess;
}

bool parseAnArgument(char* givenArgument, short& referenceToParsingTarget, std::string& responseMessage)
{
    bool resultOfRequirementCheckingProcess = false;
    int parsedValue = 0;
    std::string givenArgumentAsString = givenArgument;
    try
    {
        std::size_t positionAfterParsing;
        parsedValue = std::stoi(givenArgumentAsString, &positionAfterParsing);
        if (positionAfterParsing < givenArgumentAsString.size())
        {
            responseMessage += std::format("\nThere are some characters following the given number! ({0})", givenArgumentAsString);
        }
        else if (parsedValue < std::numeric_limits<short>::min() || parsedValue > std::numeric_limits<short>::max())
        {
            responseMessage += std::format("\nThe given number is out of range (as a short integer)! ({0})", givenArgumentAsString);

        }
        else
        {
            referenceToParsingTarget = parsedValue;
            resultOfRequirementCheckingProcess = true;
            responseMessage += std::format("\nThe given number could parsed successfully! ({0})", givenArgumentAsString);
        }
    }
    catch (std::invalid_argument const &exception)
    {
        responseMessage += std::format("\nThe given number is invalid! ({0})", givenArgumentAsString);
    }
    catch (std::out_of_range const &exception)
    {
        responseMessage += std::format("\nThe given number is out of range (as an integer)! ({0})", givenArgumentAsString);
    }

    return resultOfRequirementCheckingProcess;
}

void initializeTheConstructionPlane(BuildingType* constructionPlane, short width, short height, std::string& responseMessage)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            constructionPlane[j + i * width] = EMPTY;
        }
    }
    responseMessage = std::format("The construction plane is initialized with {0} rows and {1} columns!", height, width);
}

bool placeABuilding(BuildingType* constructionPlane, short constructionPlaneWidth, short constructionPlaneHeight, BuildingType typeOfBuildingToPlace, short positionX, short positionY, short width, short height, std::string& responseMessage)
{
    bool resultOfbuildingPlacingProcess = true;
    std::string temporaryResponseMessage = "";
    responseMessage = "x-coordinate";
    bool positionXIsWithinTheConstructionPlane = checkIfAPositionIsWithinTheConstructionPlane(constructionPlaneWidth, positionX, responseMessage);
    temporaryResponseMessage = responseMessage;
    if (positionXIsWithinTheConstructionPlane == false)
    {
        resultOfbuildingPlacingProcess = false;
    }
    responseMessage = "y-coordinate";
    bool positionYIsWithinTheConstructionPlane = checkIfAPositionIsWithinTheConstructionPlane(constructionPlaneHeight, positionY, responseMessage);
    temporaryResponseMessage += responseMessage;
    if (positionYIsWithinTheConstructionPlane == false)
    {
        resultOfbuildingPlacingProcess = false;
    }
    responseMessage = "width";
    bool buildingExceedsTheConstructionPlaneInWidth = checkIfTheBuildingExceedsTheConstructionPlaneInOneDimension(constructionPlaneWidth, positionX, width, responseMessage);
    temporaryResponseMessage += responseMessage;
    if (buildingExceedsTheConstructionPlaneInWidth == false)
    {
        resultOfbuildingPlacingProcess = false;
    }
    responseMessage = "height";
    bool buildingExceedsTheConstructionPlaneInHeight = checkIfTheBuildingExceedsTheConstructionPlaneInOneDimension(constructionPlaneHeight, positionY, height, responseMessage);
    temporaryResponseMessage += responseMessage;
    if (buildingExceedsTheConstructionPlaneInHeight == false)
    {
        resultOfbuildingPlacingProcess = false;
    }
    responseMessage = "";
    bool isThereAnyCollision = checkIfThereIsACollision(constructionPlane, constructionPlaneWidth,positionX, positionY, width, height, responseMessage);
    temporaryResponseMessage += responseMessage;
    if (isThereAnyCollision == true)
    {
        resultOfbuildingPlacingProcess = false;
    }
    responseMessage = temporaryResponseMessage;

    if (resultOfbuildingPlacingProcess == true)
    {
        for (int i = positionY - 1; i < positionY + width - 1; i++)
        {
            for (int j = positionX - 1; j < positionX + height - 1; j++)
            {
                constructionPlane[i * constructionPlaneWidth + j] = typeOfBuildingToPlace;
            }
        }
        responseMessage += "Final Result: we could successfully place a building!\n";
    }
    else
    {
        responseMessage += "Final Result: we could not place a building!\n";
    }
    return resultOfbuildingPlacingProcess;
}

bool checkIfAPositionIsWithinTheConstructionPlane(short constructionPlaneSizeInTheGivenDimension, short coordinate, std::string& responseMessage)
{
    bool resultOfPositionRangeCheckingProcess = false;
    std::string coordinateIdentifier = responseMessage;
    if (coordinate > 0)
    {
        if (coordinate <= constructionPlaneSizeInTheGivenDimension)
        {
            responseMessage = std::format("{0} is a valid value for the {1} (minimum: 1 and maximum: {2})!\n", coordinate, coordinateIdentifier, constructionPlaneSizeInTheGivenDimension);
            resultOfPositionRangeCheckingProcess = true;
        }
        else
        {
            responseMessage = std::format("{0} exceeds the valid range for the {1} (maximum: {2})!\n", coordinate, coordinateIdentifier, constructionPlaneSizeInTheGivenDimension);
        }
    }
    else
    {
        responseMessage = std::format("{0} is an invalid value for the {1} (minimum: 1)!\n", coordinate, coordinateIdentifier);
    }

    return resultOfPositionRangeCheckingProcess;
}

bool checkIfTheBuildingExceedsTheConstructionPlaneInOneDimension(short constructionPlaneSizeInTheGivenDimension, short coordinate, short buildingSizeInTheGivenDimension, std::string& responseMessage)
{
    bool resultOfSizeCheckingProcess = false;
    std::string dimensionIdentifier = responseMessage;
    if (coordinate + buildingSizeInTheGivenDimension > 0)
    {
        if (coordinate + buildingSizeInTheGivenDimension <= constructionPlaneSizeInTheGivenDimension)
        {
            resultOfSizeCheckingProcess = true;
            responseMessage = std::format("Creating a building between {0} and {1} in {2} is possible!\n", coordinate, coordinate + buildingSizeInTheGivenDimension, dimensionIdentifier);
        }
        else
        {
            responseMessage = std::format("Creating a building between {0} and {1} in {2} is not possible because it exceeds the range (maximum: {3})!\n", coordinate, coordinate + buildingSizeInTheGivenDimension, dimensionIdentifier, constructionPlaneSizeInTheGivenDimension);
        }
    }
    else
    {
        responseMessage = std::format("Creating a building between {0} and {1} in {2} is not possible because it exceeds the range (minimum: 1)!\n", coordinate, coordinate + buildingSizeInTheGivenDimension, dimensionIdentifier);
    }

    return resultOfSizeCheckingProcess;
}

bool checkIfThereIsACollision(BuildingType* constructionPlane, short constructionPlaneWidth, short positionX, short positionY, short width, short height, std::string& responseMessage)
{
    bool isThereAnyCollision = false;
    for (int i = positionY - 1; i < positionY + width - 1; i++)
    {
        for (int j = positionX - 1; j < positionX + height - 1; j++)
        {
            if (constructionPlane[i * constructionPlaneWidth + j] != EMPTY)
            {
                isThereAnyCollision = true;
                responseMessage += std::format("At position ({0},{1}) already exists a building from type {2}.\n", i, j, determineTheActualIdentifierOfABuldingTypeByIndex(constructionPlane[i * constructionPlaneWidth + j]));
            }
        }
    }
    if (isThereAnyCollision == false)
    {
        responseMessage += "We could not detect any collision!\n";

    }
    return isThereAnyCollision;
}

bool removeASpecificArea(BuildingType* constructionPlane, short constructionPlaneWidth, short constructionPlaneHeight, short positionX, short positionY, short width, short height, std::string& responseMessage)
{
    bool resultOfAreaRemovelProcess = true;
    std::string temporaryResponseMessage = "";
    responseMessage = "x-coordinate";
    bool positionXIsWithinTheConstructionPlane = checkIfAPositionIsWithinTheConstructionPlane(constructionPlaneWidth, positionX, responseMessage);
    temporaryResponseMessage = responseMessage;
    if (positionXIsWithinTheConstructionPlane == false)
    {
        resultOfAreaRemovelProcess = false;
    }
    responseMessage = "y-coordinate";
    bool positionYIsWithinTheConstructionPlane = checkIfAPositionIsWithinTheConstructionPlane(constructionPlaneHeight, positionY, responseMessage);
    temporaryResponseMessage += responseMessage;
    if (positionYIsWithinTheConstructionPlane == false)
    {
        resultOfAreaRemovelProcess = false;
    }
    responseMessage = "width";
    bool buildingExceedsTheConstructionPlaneInWidth = checkIfTheBuildingExceedsTheConstructionPlaneInOneDimension(constructionPlaneWidth, positionX, width, responseMessage);
    temporaryResponseMessage += responseMessage;
    if (buildingExceedsTheConstructionPlaneInWidth == false)
    {
        resultOfAreaRemovelProcess = false;
    }
    responseMessage = "height";
    bool buildingExceedsTheConstructionPlaneInHeight = checkIfTheBuildingExceedsTheConstructionPlaneInOneDimension(constructionPlaneHeight, positionY, height, responseMessage);
    temporaryResponseMessage += responseMessage;
    if (buildingExceedsTheConstructionPlaneInHeight == false)
    {
        resultOfAreaRemovelProcess = false;
    }
    responseMessage = temporaryResponseMessage;

    if (resultOfAreaRemovelProcess == true)
    {
        for (int i = positionY - 1; i < positionY + width - 1; i++)
        {
            for (int j = positionX - 1; j < positionX + height - 1; j++)
            {
                constructionPlane[i * constructionPlaneWidth + j] = EMPTY;
            }
        }
        responseMessage += "Final Result: we could successfully remove an area!\n";
    }
    else
    {
        responseMessage += "Final Result: we could not remove an area!\n";
    }
    return resultOfAreaRemovelProcess;

}
void displayTheConstructionPlane(BuildingType* constructionPlane, short width, short height)
{
    std::string currentBuildingTypeAsString = "-";
    BuildingType currentBuildingType = EMPTY;
    std::string constructionPlaneAsString = "\nConstruction Plane\n\n";
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            currentBuildingTypeAsString = determineTheActualIdentifierOfABuldingTypeByIndex(constructionPlane[j + i * width]);

            constructionPlaneAsString += std::format(" {} ", currentBuildingTypeAsString);
        }
        constructionPlaneAsString += "\n";
    }

    std::cout << constructionPlaneAsString << std::endl;
}

std::string determineTheActualIdentifierOfABuldingTypeByIndex(short index)
{
    std::string buildingTypeAsString = "-";
    switch (index)
    {
    case EMPTY:
        buildingTypeAsString = "-";
        break;
    case HYDROELECTRIC_POWER_PLANT:
        buildingTypeAsString = "H";
        break;
    case WIND_POWER_PLANT:
        buildingTypeAsString = "W";
        break;
    case SOLAR_PANEL:
        buildingTypeAsString = "S";
        break;
    default:
        break;
    }

    return buildingTypeAsString;
}
void terminateTheProgram(void)
{
    std::cout << "Nice to have you there! See you next time!" << std::endl;
    exit(EXIT_SUCCESS);
}
