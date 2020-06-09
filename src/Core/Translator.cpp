/*
 * Copyright (C) 2019-2020 Ashar Khan <ashar786khan@gmail.com>
 *
 * This file is part of CP Editor.
 *
 * CP Editor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * I will not be responsible if CP Editor behaves in unexpected way and
 * causes your ratings to go down and or lose any important contest.
 *
 * Believe Software is "Software" and it isn't immune to bugs.
 *
 */

#include "Core/Translator.hpp"
#include "Core/EventLogger.hpp"
#include "generated/SettingsInfo.hpp"
#include <QMap>
#include <QTranslator>

namespace Core
{
const static QMap<QString, QString> locales = {{"简体中文", "SimplifiedChinese"},
                                               // {"繁體中文", "TraditionalChinese"},
                                               {"Русский", "Russian"}};

QTranslator *Translator::translator = nullptr;

void Translator::setLocale(const QString &language)
{
    LOG_INFO(INFO_OF(language));
    if (translator)
    {
        LOG_ERR_IF(!qApp->removeTranslator(translator), "Failed to remove the translator " << translator);
        delete translator;
        translator = nullptr;
    }
    if (locales.keys().contains(language))
    {
        translator = new QTranslator(qApp);
        translator->load(QString(":/translations/%1.qm").arg(locales[language]));
        LOG_ERR_IF(!qApp->installTranslator(translator), "Failed to load the translator " << translator);
        updateSettingInfo();
    }
}
} // namespace Core
