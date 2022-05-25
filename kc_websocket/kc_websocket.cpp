// kc_websocket.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include "websocket_base.hpp"
#include <iostream>

#include <thread>

int main() {
  boost::asio::io_context ioContext(std::thread::hardware_concurrency());
  boost::asio::ssl::context sslContext(
      boost::asio::ssl::context_base::tlsv12_client);
  sslContext.set_default_verify_paths();
  sslContext.set_verify_mode(boost::asio::ssl::verify_none);

  auto const tradeType = korrelator::trade_type_e::futures;
  korrelator::kc_websocket socket(ioContext, sslContext, tradeType);

  if (tradeType == korrelator::trade_type_e::spot) {
    socket.addSubscription("BTC-USDT");
    socket.addSubscription("RUNE-USDT");
  } else {
    socket.addSubscription("XBTUSDTM");
    socket.addSubscription("ETHUSDTM");
  }
  socket.startFetching();
  ioContext.run();
}
