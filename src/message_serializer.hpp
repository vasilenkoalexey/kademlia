// Copyright (c) 2014, David Keller
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the University of California, Berkeley nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY DAVID KELLER AND CONTRIBUTORS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef KADEMLIA_MESSAGE_SERIALIZER_HPP
#define KADEMLIA_MESSAGE_SERIALIZER_HPP

#ifdef _MSC_VER
#   pragma once
#endif

#include <memory>

#include "message.hpp"

namespace kademlia {
namespace detail {

/**
 *
 */
class message_serializer
{
public:
    /**
     *
     */
    message_serializer
        ( id const& my_id );

    /**
     *
     */
    template< typename Message >
    buffer
    serialize
        ( Message const& message
        , id const& token );

    /**
     *
     */
    buffer
    serialize
        ( header::type const& type
        , id const& token );

private:
    /**
     *
     */
    header
    generate_header
        ( header::type const& type
        , id const& token );

private:
    ///
    id const& my_id_;
};

template< typename Message >
buffer
message_serializer::serialize
    ( Message const& message
    , id const& token )
{
    auto const type = message_traits< Message >::TYPE_ID;
    auto const header = generate_header( type, token );

    buffer b;
    detail::serialize( header, b );
    detail::serialize( message, b );

    return std::move( b );
}

} // namespace detail
} // namespace kademlia

#endif

