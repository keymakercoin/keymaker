// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_WALLET_COINCONTROL_H
#define BITCOIN_WALLET_COINCONTROL_H

#include <key.h>
#include <optional.h>
#include <policy/feerate.h>
#include <policy/fees.h>
#include <primitives/transaction.h>
#include <script/standard.h>

enum class CoinType {
    ALL_COINS,
    ONLY_FULLY_MIXED,
    ONLY_READY_TO_MIX,
    ONLY_NONDENOMINATED,
    ONLY_SMARTNODE_COLLATERAL, // find smartnode outputs including locked ones (use with caution)
    ONLY_COINJOIN_COLLATERAL,
    // Attributes
    MIN_COIN_TYPE = ALL_COINS,
    MAX_COIN_TYPE = ONLY_COINJOIN_COLLATERAL,
};

/** Coin Control Features. */
class CCoinControl {
public:
    CTxDestination destChange;
    CTxDestination assetDestChange;
    //! If false, allows unselected inputs, but requires all selected inputs be used if fAllowOtherInputs is true (default)
    bool fAllowOtherInputs;
    //! If false, only include as many inputs as necessary to fulfill a coin selection request. Only usable together with fAllowOtherInputs
    bool fRequireAllInputs;
    //! Includes watch only addresses which match the ISMINE_WATCH_SOLVABLE criteria
    bool fAllowWatchOnly;
    //! Override automatic min/max checks on fee, m_feerate must be set if true
    bool fOverrideFeeRate;
    //! Override the wallet's m_pay_tx_fee if set
    Optional <CFeeRate> m_feerate;
    //! Override the discard feerate estimation with m_discard_feerate in CreateTransaction if set
    Optional <CFeeRate> m_discard_feerate;
    //! Override the default confirmation target if set
    Optional<unsigned int> m_confirm_target;
    //! Avoid partial use of funds sent to given address
    bool m_avoid_partial_spends;
    //! Fee estimation mode to control arguments to estimateSmartFee
    FeeEstimateMode m_fee_mode;
    //! Minimum chain depth value for coin availability
    int m_min_depth{0};
    //! Controls which types of coins are allowed to be used (default: ALL_COINS)
    CoinType nCoinType;
    //! Asset id of the asset that is selected, used when sending assets with coincontrol
    std::string strAssetSelected;

    CCoinControl() {
        SetNull();
    }

    void SetNull(bool fResetCoinType = true);

    bool HasSelected() const {
        return (setSelected.size() > 0);
    }

    bool HasAssetSelected() const {
        return (setAssetsSelected.size() > 0);
    }

    bool IsSelected(const COutPoint &output) const {
        return (setSelected.count(output) > 0);
    }

    bool IsAssetSelected(const COutPoint &output) const {
        return (setAssetsSelected.count(output) > 0);
    }

    void Select(const COutPoint &output) {
        setSelected.insert(output);
    }

    void SelectAsset(const COutPoint &output) {
        setAssetsSelected.insert(output);
    }

    void UnSelect(const COutPoint &output) {
        setSelected.erase(output);
    }

    void UnSelectAsset(const COutPoint &output) {
        setAssetsSelected.erase(output);
        if (!setSelected.size())
            strAssetSelected = "";
    }

    void UnSelectAll() {
        setSelected.clear();
        strAssetSelected = "";
        setAssetsSelected.clear();
    }

    void ListSelected(std::vector <COutPoint> &vOutpoints) const {
        vOutpoints.assign(setSelected.begin(), setSelected.end());
    }

    void ListSelectedAssets(std::vector <COutPoint> &vOutpoints) const {
        vOutpoints.assign(setAssetsSelected.begin(), setAssetsSelected.end());
    }
    // Keymaker-specific helpers

    void UseCoinJoin(bool fUseCoinJoin) {
        nCoinType = fUseCoinJoin ? CoinType::ONLY_FULLY_MIXED : CoinType::ALL_COINS;
    }

    bool IsUsingCoinJoin() const {
        return nCoinType == CoinType::ONLY_FULLY_MIXED;
    }

private:
    std::set <COutPoint> setSelected;
    std::set <COutPoint> setAssetsSelected;
};

#endif // BITCOIN_WALLET_COINCONTROL_H