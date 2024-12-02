// Copyright (c) 2024 The Keymaker developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KEYMAKER_UPLOAD_DOWNLOAD_H
#define KEYMAKER_UPLOAD_DOWNLOAD_H

#include <util/system.h>

#include <iostream>
#include <vector>
#include <string>
#include <QWidget>

static std::string GET_URI = "/get/";
static std::string UPLOAD_URI = "/upload";
static std::string DEFAULT_IPFS_SERVICE_URL = "ipfsm.keymaker.com";
static std::string DEFAULT_IPFS_GATEWAY_URL = "https://ipfsweb.keymaker.com/ipfs/";

void download(const std::string cid, std::string& response_data);
void upload(const std::string& file_path, std::string& response_data);
void pickAndUploadFileForIpfs(QWidget *qWidget, std::string& cid);

#endif //KEYMAKER_UPLOAD_DOWNLOAD_H
