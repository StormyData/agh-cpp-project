//
// Created by tobiasz on 21.05.2022.
//

#include "Collidable.h"
#include "common.h"

bool Collidable::colides(const Collidable &other) {

    return this->sat(other) && other.sat(*this);
}

Collidable::Collidable(const ColisionData& data): data(data) {
    min_max_arr.reserve(data.points.size());
    axes.reserve(data.points.size());
    for(size_t i=0;i<data.points.size();i++)
    {
        float min = INFINITY;
        float max = -INFINITY;
        sf::Vector2f axis = data.points[i>0? i - 1: data.points.size() -1] - data.points[i];
        axis = util::normalize(util::rotate_90_degrees_clockwise(axis));
        axes.push_back(axis);

        for(sf::Vector2f vertex : data.points)
        {
            float tmp = util::dot(axis, vertex);
            if(tmp < min)
                min = tmp;
            if(tmp > max)
                max = tmp;
        }
        min_max_arr.emplace_back(min, max);
    }
}

bool Collidable::sat(const Collidable &other) const {
    if(axes.empty())
        return false;
    for(size_t i=0;i<axes.size();i++)
    {
        sf::Vector2f axis = axes[i];
        float min = INFINITY;
        float max = -INFINITY;

        float this_pos_offset = util::dot(axis, position);
        float other_pos_offset = util::dot(axis, other.position);
        for(sf::Vector2f vertex : other.data.points)
        {

            float tmp = util::dot(axis, vertex);
            if(tmp < min)
                min = tmp;
            if(tmp > max)
                max = tmp;
        }
        if(min_max_arr[i].first + this_pos_offset > max + other_pos_offset
        || min + other_pos_offset > min_max_arr[i].second + this_pos_offset)
            return false;
    }
    return true;
}
