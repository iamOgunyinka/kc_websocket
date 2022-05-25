#include "uri.hpp"
#include <algorithm>
#include <iterator>

namespace korrelator {

uri::uri(std::string const &url_s) { parse(url_s); }

std::string uri::target() const { return m_path + "?" + m_query; }

std::string uri::protocol() const { return m_protocol; }

std::string uri::path() const { return m_path; }

std::string uri::host() const { return m_host; }

void uri::parse(std::string const &url_s) {
  std::string const prot_end{"://"};
  std::string::const_iterator prot_i =
      std::search(url_s.begin(), url_s.end(), prot_end.begin(), prot_end.end());
  m_protocol.reserve(
      static_cast<std::size_t>(std::distance(url_s.cbegin(), prot_i)));
  std::transform(url_s.begin(), prot_i, std::back_inserter(m_protocol),
                 [](int c) { return std::tolower(c); });
  if (prot_i == url_s.end()) {
    prot_i = url_s.begin();
  } else {
    std::advance(prot_i, prot_end.length());
  }

  std::string::const_iterator path_i = std::find(prot_i, url_s.end(), '/');
  m_host.reserve(static_cast<std::size_t>(std::distance(prot_i, path_i)));
  std::transform(prot_i, path_i, std::back_inserter(m_host),
                 [](int c) { return std::tolower(c); });
  std::string::const_iterator query_i = std::find(path_i, url_s.end(), '?');
  m_path.assign(path_i, query_i);
  if (query_i != url_s.end())
    ++query_i;
  m_query.assign(query_i, url_s.end());
}

} // namespace korrelator
