// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2022 Thomas Basler and others
 */
#include "WebApi_gridprofile.h"
#include "WebApi.h"
#include <AsyncJson.h>
#include <InverterHandler.h>

void WebApiGridProfileClass::init(AsyncWebServer* server)
{
    using std::placeholders::_1;

    _server = server;

    _server->on("/api/gridprofile/status", HTTP_GET, std::bind(&WebApiGridProfileClass::onGridProfileStatus, this, _1));
}

void WebApiGridProfileClass::loop()
{
}

void WebApiGridProfileClass::onGridProfileStatus(AsyncWebServerRequest* request)
{
    if (!WebApi.checkCredentialsReadonly(request)) {
        return;
    }

    AsyncJsonResponse* response = new AsyncJsonResponse(false, 4096);
    JsonObject root = response->getRoot();

    uint64_t serial = 0;
    if (request->hasParam("inv")) {
        String s = request->getParam("inv")->value();
        serial = strtoll(s.c_str(), NULL, 16);
    }


    if(!request->hasParam("manufacturer")){
        response->setCode(400);
        response->setLength();
        request->send(response);
        return;
    }

    auto type = to_inverter_type(request->getParam("manufacturer")->value());

    if(type == inverter_type::Inverter_count){
        response->setCode(400);
        response->setLength();
        request->send(response);
        return;
    }

    auto inv = InverterHandler.getInverterBySerial(serial,type);

    if (inv != nullptr) {
        auto raw = root.createNestedArray("raw");
        auto data = inv->GridProfile()->getRawData();

        copyArray(&data[0], data.size(), raw);
    }

    response->setLength();
    request->send(response);
}