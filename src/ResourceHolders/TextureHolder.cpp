#include "TextureHolder.h"

#include <cassert>
#include <iostream>

TextureHolder::TextureHolder() {
    resourceMap[TextureID::None] = std::make_unique<Texture2D>();
}

TextureHolder::~TextureHolder() {
    for (auto& p : resourceMap) {
        UnloadTexture(*p.second);
    }
}

TextureHolder& TextureHolder::getInstance() {
    static TextureHolder instance;
    return instance;
}

void TextureHolder::load(TextureID id, const std::string& filename) {
    std::unique_ptr<Texture2D> resource(new Texture());
    *resource = LoadTexture(filename.c_str());
    insertResource(id, std::move(resource));
}

Texture2D& TextureHolder::get(TextureID id) {
    auto found = resourceMap.find(id);
    if (found == resourceMap.end()) {
        return *resourceMap[TextureID::None];
    }
    SetTextureFilter(*found->second, TEXTURE_FILTER_BILINEAR);
    return *found->second;
}

const Texture2D& TextureHolder::get(TextureID id) const {
    auto found = resourceMap.find(id);
    if (found == resourceMap.end()) {
        return *resourceMap.at(TextureID::None);
    }
    SetTextureFilter(*found->second, TEXTURE_FILTER_BILINEAR);
    return *found->second;
}

void TextureHolder::insertResource(TextureID id,
                                   std::unique_ptr<Texture2D> resource) {
    auto insertStatus = resourceMap.emplace(id, std::move(resource));
    assert(insertStatus.second == true);
}
