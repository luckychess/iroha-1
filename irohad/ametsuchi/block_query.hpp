/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef IROHA_BLOCK_QUERY_HPP
#define IROHA_BLOCK_QUERY_HPP

#include <boost/optional.hpp>
#include "ametsuchi/tx_cache_response.hpp"
#include "common/result.hpp"
#include "interfaces/iroha_internal/block.hpp"

namespace iroha {

  namespace ametsuchi {
    /**
     * Public interface for queries on blocks and transactions
     */
    class BlockQuery {
     public:
      using BlockResult =
          expected::Result<std::unique_ptr<shared_model::interface::Block>,
                           std::string>;

      virtual ~BlockQuery() = default;

      /**
       * Retrieve block with given height from block storage
       * @param height - height of a block to retrieve
       * @return block with given height
       */
      virtual BlockResult getBlock(
          shared_model::interface::types::HeightType height) = 0;

      /**
       * Get height of the top block.
       * @return height
       */
      virtual shared_model::interface::types::HeightType
      getTopBlockHeight() = 0;

      /**
       * Synchronously checks whether transaction with given hash is present in
       * any block
       * @param hash - transaction's hash
       * @return TxCacheStatusType which returns status (Committed, Rejected or
       * Missing) of transaction if storage query was successful, boost::none
       * otherwise
       */
      virtual boost::optional<TxCacheStatusType> checkTxPresence(
          const shared_model::crypto::Hash &hash) = 0;
    };
  }  // namespace ametsuchi
}  // namespace iroha

#endif  // IROHA_BLOCK_QUERY_HPP
