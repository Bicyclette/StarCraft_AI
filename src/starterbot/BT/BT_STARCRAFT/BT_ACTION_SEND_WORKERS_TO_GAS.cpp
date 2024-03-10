#include "BT_ACTION_SEND_WORKERS_TO_GAS.h"
#include "Tools.h"
#include "Data.h"

BT_ACTION_SEND_WORKERS_TO_GAS::BT_ACTION_SEND_WORKERS_TO_GAS(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State BT_ACTION_SEND_WORKERS_TO_GAS::Evaluate(void* data)
{
    return ReturnState(SendWorkersToGas(data));
}

std::string BT_ACTION_SEND_WORKERS_TO_GAS::GetDescription()
{
    return "SEND WORKERS TO GAS";
}


BT_NODE::State BT_ACTION_SEND_WORKERS_TO_GAS::SendWorkersToGas(void* data)
{
    Data* pData = (Data*)data;
    const int howManyToSend = pData->wantedProbesOnGas - pData->probesOnGas;

    std::cout << "Called send to gas";

    Tools::SendProbesToGas(howManyToSend);
    pData->justSentToGas = true;

    return BT_NODE::SUCCESS;
}