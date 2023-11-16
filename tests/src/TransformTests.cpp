#pragma once

#include "Pulsarion.h"
#include "Pulsarion/Core/Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stfcpp/include/stfcpp/stfcpp.h>

using namespace Pulsarion;

STF_TEST_SUITE(TransformTests)
{
    void test_translation()
    {
        Transform2D transform;
        transform.SetTranslation(glm::vec2(1.0f, 2.0f));
        glm::mat4 matrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(1.0f, 2.0f, 0.0f));
        STF_BASIC_ASSERT(matrix, transform.GetAsMatrix(), "Translated matrix does match the matrix given by Transform!");
    }

    void test_rotation()
    {
        Transform2D transform;
        transform.SetRotation(glm::half_pi<float>());
        glm::mat4 matrix = glm::rotate(glm::identity<glm::mat4>(), glm::half_pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
        STF_BASIC_ASSERT(matrix, transform.GetAsMatrix(), "Rotated matrix does match the matrix given by Transform!");
    }

    void test_scale()
    {
        Transform2D transform;
        transform.SetScale(glm::vec2(1.0f, 2.0f));
        glm::mat4 matrix = glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.0f, 2.0f, 1.0f));
        STF_BASIC_ASSERT(matrix, transform.GetAsMatrix(), "Scaled matrix does match the matrix given by Transform!");
    }

    void test_matrix()
    {
        Transform2D transform;
        transform.SetTranslation(glm::vec2(1.0f, 2.0f));
        transform.SetRotation(glm::half_pi<float>());
        transform.SetScale(glm::vec2(1.0f, 2.0f));
        glm::mat4 matrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(1.0f, 2.0f, 0.0f));
        matrix = glm::rotate(matrix, glm::half_pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
        matrix = glm::scale(matrix, glm::vec3(1.0f, 2.0f, 1.0f));
        STF_BASIC_ASSERT(matrix, transform.GetAsMatrix(), "Matrix does match the matrix given by Transform!");
    }

    STF_SUITE_TEST(TranslationTest, test_translation);
    STF_SUITE_TEST(RotationTest, test_rotation);
    STF_SUITE_TEST(ScaleTest, test_scale);
    STF_SUITE_TEST(MatrixTest, test_matrix);
};
STF_REGISTER_SUITE(TransformTests);
