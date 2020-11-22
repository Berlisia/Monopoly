#pragma once
#include <QWidget>
#include <memory>
#include <string>

class Field
{
public:
    Field(std::string path, std::string name) : cardName(name), pixmap(std::make_unique<QPixmap>(path.c_str())) {}
    Field(Field&&) = default;

    std::string cardName;
    std::unique_ptr<QPixmap> pixmap;
};