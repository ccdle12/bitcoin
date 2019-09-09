// Copyright (c) 2017-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <consensus/tx_check.h>

#include <primitives/transaction.h>
#include <consensus/validation.h>

#include <iostream>

bool CheckTransaction(const CTransaction& tx, CValidationState &state, bool fCheckDuplicateInputs)
{
    std::cout << "DEBUG CCDLE12: CheckTransaction" << std::endl;
    // Basic checks that don't depend on any context
    /* std::cout << "DEBUG CCDLE12: TXVIN ToString(): " << tx.vin.ToString() << std::endl; */
    for (const auto& tx : tx.vin)
    {
        std::cout << "DEBUG CCDLE12: TXVIN ToString(): " << tx.ToString() << std::endl;
    }
    if (tx.vin.empty())
        return state.Invalid(ValidationInvalidReason::CONSENSUS, false, REJECT_INVALID, "bad-txns-vin-empty");
    /* std::cout << "DEBUG CCDLE12: TXOUT ToString(): " << tx.vout.ToString() << std::endl; */
    for (const auto& tx : tx.vout)
    {
        std::cout << "DEBUG CCDLE12: TXOUT ToString(): " << tx.ToString() << std::endl;
    }
    if (tx.vout.empty())
        return state.Invalid(ValidationInvalidReason::CONSENSUS, false, REJECT_INVALID, "bad-txns-vout-empty");
    // Size limits (this doesn't take the witness into account, as that hasn't been checked for malleability)
    if (::GetSerializeSize(tx, PROTOCOL_VERSION | SERIALIZE_TRANSACTION_NO_WITNESS) * WITNESS_SCALE_FACTOR > MAX_BLOCK_WEIGHT)
        return state.Invalid(ValidationInvalidReason::CONSENSUS, false, REJECT_INVALID, "bad-txns-oversize");

    // Check for negative or overflow output values
    CAmount nValueOut = 0;
    for (const auto& txout : tx.vout)
    {
        std::cout << "DEBUG CCDLE12: TXOUT nValue: " << txout.nValue << std::endl;
        if (txout.nValue < 0)
            return state.Invalid(ValidationInvalidReason::CONSENSUS, false, REJECT_INVALID, "bad-txns-vout-negative");

        std::cout << "DEBUG CCDLE12: TXOUT MAX_MONEY: " << MAX_MONEY << std::endl;
        if (txout.nValue > MAX_MONEY)
            return state.Invalid(ValidationInvalidReason::CONSENSUS, false, REJECT_INVALID, "bad-txns-vout-toolarge");
        std::cout << "DEBUG CCDLE12: Adds each value to the output: " << nValueOut << std::endl;
        nValueOut += txout.nValue;
        // Make sure the output of the transaction is greater than 0 and less than the total.
        if (!MoneyRange(nValueOut))
            return state.Invalid(ValidationInvalidReason::CONSENSUS, false, REJECT_INVALID, "bad-txns-txouttotal-toolarge");
    }

    // Check for duplicate inputs - note that this check is slow so we skip it in CheckBlock
    if (fCheckDuplicateInputs) {
        std::set<COutPoint> vInOutPoints;
        for (const auto& txin : tx.vin)
        {
            if (!vInOutPoints.insert(txin.prevout).second)
                return state.Invalid(ValidationInvalidReason::CONSENSUS, false, REJECT_INVALID, "bad-txns-inputs-duplicate");
        }
    }

    if (tx.IsCoinBase())
    {
        if (tx.vin[0].scriptSig.size() < 2 || tx.vin[0].scriptSig.size() > 100)
            return state.Invalid(ValidationInvalidReason::CONSENSUS, false, REJECT_INVALID, "bad-cb-length");
    }
    else
    {
        for (const auto& txin : tx.vin)
            if (txin.prevout.IsNull())
                return state.Invalid(ValidationInvalidReason::CONSENSUS, false, REJECT_INVALID, "bad-txns-prevout-null");
    }

    return true;
}
