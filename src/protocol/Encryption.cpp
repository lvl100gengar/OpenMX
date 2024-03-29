#include "Encryption.h"
#include <algorithm>
#include <cstdlib>

namespace OpenMX {

constexpr unsigned char table0[] = { 63, 175, 37, 147, 189, 180, 35, 243, 85, 185, 197, 173, 49, 177, 139, 72, 46, 39, 182, 221, 214, 116, 153, 239, 92, 25, 144, 70, 89, 252, 125, 171, 82, 91, 93, 7, 51, 244, 18, 21, 130, 38, 14, 184, 98, 74, 250, 238, 105, 58, 6, 87, 10, 114, 249, 45, 155, 53, 40, 201, 226, 136, 240, 235, 33, 73, 75, 68, 24, 42, 19, 225, 149, 96, 54, 227, 13, 132, 255, 190, 166, 230, 32, 108, 143, 113, 55, 215, 80, 198, 247, 101, 254, 117, 169, 12, 217, 234, 11, 100, 248, 112, 107, 77, 174, 131, 236, 111, 109, 191, 216, 228, 187, 79, 66, 220, 110, 2, 152, 218, 34, 36, 193, 83, 210, 60, 56, 229, 23, 15, 154, 28, 120, 129, 69, 126, 59, 134, 161, 151, 95, 115, 27, 148, 242, 209, 67, 206, 124, 165, 253, 17, 88, 123, 145, 1, 127, 118, 223, 119, 224, 159, 188, 122, 207, 48, 164, 50, 52, 156, 84, 202, 61, 231, 86, 137, 8, 178, 106, 103, 22, 219, 199, 232, 3, 237, 64, 31, 99, 208, 246, 97, 157, 138, 158, 181, 41, 71, 200, 26, 142, 128, 90, 204, 104, 44, 212, 222, 196, 57, 162, 78, 121, 30, 168, 205, 160, 211, 150, 245, 176, 102, 5, 0, 241, 172, 194, 233, 213, 133, 4, 163, 81, 251, 141, 9, 43, 76, 94, 186, 16, 65, 179, 146, 167, 135, 62, 140, 195, 183, 170, 47, 20, 29, 203, 192 };
constexpr unsigned char table1[] = { 223, 155, 117, 184, 230, 222, 50, 35, 176, 235, 52, 98, 95, 76, 42, 129, 240, 151, 38, 70, 252, 39, 180, 128, 68, 25, 199, 142, 131, 253, 213, 187, 82, 64, 120, 6, 121, 2, 41, 17, 58, 196, 69, 236, 205, 55, 16, 251, 165, 12, 167, 36, 168, 57, 74, 86, 126, 209, 49, 136, 125, 172, 246, 0, 186, 241, 114, 146, 67, 134, 27, 197, 15, 65, 45, 66, 237, 103, 211, 113, 88, 232, 32, 123, 170, 8, 174, 51, 152, 28, 202, 33, 24, 34, 238, 140, 73, 191, 44, 188, 99, 91, 221, 179, 204, 48, 178, 102, 83, 108, 116, 107, 101, 85, 53, 141, 21, 93, 157, 159, 132, 212, 163, 153, 148, 30, 135, 156, 201, 133, 40, 105, 77, 229, 137, 245, 61, 175, 193, 14, 247, 234, 200, 84, 26, 154, 243, 3, 143, 72, 218, 139, 118, 22, 130, 56, 169, 192, 194, 161, 216, 138, 210, 231, 166, 149, 80, 244, 214, 94, 250, 31, 225, 11, 104, 1, 220, 13, 177, 242, 5, 195, 18, 249, 43, 9, 239, 112, 162, 4, 79, 109, 255, 122, 226, 248, 208, 10, 89, 182, 198, 59, 171, 254, 203, 215, 147, 164, 189, 145, 124, 217, 206, 228, 20, 87, 110, 96, 119, 181, 115, 19, 207, 158, 160, 71, 60, 75, 111, 127, 81, 173, 183, 227, 97, 63, 106, 185, 47, 23, 62, 224, 144, 7, 37, 219, 190, 90, 100, 54, 46, 233, 29, 150, 92, 78 };
constexpr unsigned char table2[] = { 210, 58, 116, 175, 181, 169, 206, 147, 70, 150, 71, 205, 168, 105, 247, 35, 129, 120, 251, 19, 141, 45, 69, 142, 27, 174, 15, 34, 185, 56, 103, 74, 228, 39, 170, 82, 32, 76, 153, 60, 41, 148, 48, 232, 188, 66, 123, 253, 229, 252, 64, 145, 59, 239, 79, 242, 186, 101, 49, 243, 224, 165, 24, 219, 102, 46, 67, 107, 180, 182, 80, 42, 18, 249, 54, 248, 138, 47, 199, 179, 178, 230, 195, 51, 118, 114, 128, 245, 146, 171, 133, 16, 194, 203, 151, 29, 212, 207, 84, 88, 197, 72, 77, 95, 193, 183, 92, 37, 52, 240, 115, 235, 173, 20, 191, 94, 6, 31, 254, 97, 113, 234, 1, 36, 125, 8, 157, 132, 91, 43, 78, 244, 65, 87, 163, 83, 0, 11, 93, 12, 30, 161, 63, 75, 28, 100, 40, 140, 154, 96, 198, 38, 25, 204, 99, 136, 241, 9, 143, 13, 4, 189, 139, 213, 220, 159, 135, 222, 190, 126, 149, 81, 200, 90, 17, 218, 112, 61, 104, 127, 62, 233, 201, 89, 215, 110, 121, 106, 21, 208, 119, 137, 111, 162, 2, 134, 227, 144, 166, 158, 108, 5, 14, 250, 211, 217, 98, 109, 22, 192, 226, 3, 131, 23, 214, 164, 10, 124, 57, 26, 223, 236, 33, 44, 176, 68, 155, 187, 117, 7, 122, 196, 160, 167, 246, 184, 177, 172, 255, 237, 202, 130, 225, 209, 156, 152, 85, 216, 231, 86, 238, 53, 73, 221, 50, 55 };
constexpr unsigned char table3[] = { 136, 122, 194, 211, 160, 201, 116, 229, 125, 157, 216, 137, 139, 159, 202, 26, 91, 174, 72, 19, 113, 188, 208, 213, 62, 152, 219, 24, 144, 95, 140, 117, 36, 222, 27, 15, 123, 107, 151, 33, 146, 40, 71, 129, 223, 21, 65, 77, 42, 58, 254, 83, 108, 251, 74, 255, 29, 218, 1, 52, 39, 177, 180, 142, 50, 132, 45, 66, 225, 22, 8, 10, 101, 252, 31, 143, 37, 102, 130, 54, 70, 171, 35, 135, 98, 246, 249, 133, 99, 183, 173, 128, 106, 138, 115, 103, 149, 119, 206, 154, 145, 57, 64, 30, 178, 13, 187, 67, 200, 207, 185, 192, 176, 120, 85, 110, 2, 228, 84, 190, 17, 186, 230, 46, 217, 124, 169, 179, 86, 16, 241, 212, 127, 90, 195, 166, 155, 191, 76, 162, 147, 20, 23, 158, 197, 51, 88, 7, 41, 170, 9, 94, 245, 38, 148, 226, 244, 126, 199, 165, 232, 141, 193, 134, 215, 61, 198, 233, 12, 5, 34, 89, 237, 112, 25, 3, 224, 236, 80, 79, 68, 4, 69, 105, 235, 28, 56, 227, 44, 161, 168, 114, 209, 104, 92, 82, 231, 100, 150, 78, 172, 182, 240, 93, 153, 11, 6, 97, 189, 243, 0, 204, 96, 163, 214, 184, 247, 205, 175, 63, 164, 253, 167, 220, 60, 242, 210, 196, 32, 48, 81, 248, 43, 181, 121, 111, 221, 239, 250, 53, 109, 156, 55, 59, 131, 87, 234, 14, 75, 73, 203, 18, 49, 47, 118, 238 };
constexpr unsigned char table4[] = { 22, 36, 237, 37, 168, 85, 93, 26, 225, 3, 104, 76, 78, 250, 253, 110, 58, 234, 241, 244, 246, 33, 157, 127, 68, 207, 45, 77, 13, 150, 99, 19, 143, 220, 7, 201, 235, 62, 49, 74, 164, 166, 122, 114, 240, 4, 227, 108, 5, 25, 183, 72, 61, 171, 20, 243, 186, 214, 217, 181, 11, 107, 212, 119, 215, 141, 88, 46, 135, 230, 102, 64, 52, 252, 24, 245, 133, 222, 39, 198, 27, 124, 32, 17, 200, 144, 139, 111, 40, 148, 23, 161, 84, 231, 236, 18, 226, 0, 248, 165, 213, 142, 218, 195, 34, 251, 128, 184, 209, 106, 57, 81, 242, 126, 94, 6, 191, 75, 130, 152, 138, 97, 233, 73, 125, 28, 175, 153, 154, 70, 192, 131, 10, 21, 193, 160, 31, 239, 169, 92, 219, 134, 179, 172, 30, 66, 129, 105, 63, 223, 210, 180, 38, 155, 86, 41, 98, 109, 9, 162, 224, 60, 54, 205, 136, 116, 101, 149, 146, 199, 177, 48, 118, 194, 59, 43, 216, 95, 53, 16, 117, 44, 140, 96, 173, 8, 132, 211, 229, 90, 167, 203, 12, 42, 51, 55, 50, 35, 190, 89, 196, 202, 178, 189, 123, 151, 79, 185, 163, 174, 176, 197, 14, 69, 115, 113, 87, 91, 249, 254, 65, 238, 145, 147, 121, 182, 170, 71, 56, 137, 1, 100, 187, 47, 29, 158, 221, 208, 120, 80, 67, 232, 112, 228, 204, 82, 2, 103, 247, 156, 188, 206, 15, 83, 159, 255,
    97, 230, 246, 9, 45, 48, 115, 34, 185, 158, 132, 60, 192, 28, 212, 252, 179, 83, 95, 31, 54, 133, 0, 90, 74, 49, 7, 80, 125, 234, 144, 136, 82, 21, 104, 197, 1, 3, 152, 78, 88, 155, 193, 175, 181, 26, 67, 233, 171, 38, 196, 194, 72, 178, 162, 195, 228, 110, 16, 174, 161, 52, 37, 148, 71, 220, 145, 240, 24, 213, 129, 227, 51, 123, 39, 117, 11, 27, 12, 206, 239, 111, 245, 253, 92, 5, 154, 216, 66, 199, 189, 217, 139, 6, 114, 177, 183, 121, 156, 30, 231, 166, 70, 247, 10, 147, 109, 61, 47, 157, 15, 87, 242, 215, 43, 214, 165, 180, 172, 63, 238, 224, 42, 204, 81, 124, 113, 23, 106, 146, 118, 131, 186, 76, 141, 68, 164, 229, 120, 86, 182, 65, 101, 32, 85, 222, 168, 223, 89, 167, 29, 205, 119, 127, 128, 153, 249, 22, 235, 254, 135, 91, 159, 208, 40, 99, 41, 190, 4, 138, 226, 53, 143, 184, 209, 126, 210, 170, 202, 142, 151, 59, 225, 50, 107, 207, 56, 232, 250, 203, 198, 116, 130, 134, 173, 103, 200, 211, 79, 169, 84, 35, 201, 191, 244, 163, 251, 25, 237, 108, 150, 187, 62, 100, 57, 64, 176, 58, 102, 140, 33, 236, 77, 149, 160, 8, 96, 46, 243, 188, 69, 93, 241, 122, 17, 36, 94, 2, 221, 137, 44, 18, 112, 55, 19, 75, 20, 248, 98, 218, 13, 105, 73, 14, 219, 255 };
constexpr unsigned char table6[] = { 173, 51, 110, 53, 59, 145, 99, 69, 80, 79, 249, 35, 96, 242, 244, 2, 62, 213, 105, 148, 211, 255, 152, 41, 180, 243, 108, 160, 82, 159, 144, 207, 221, 48, 15, 112, 204, 134, 123, 216, 56, 157, 254, 33, 184, 120, 109, 31, 142, 140, 64, 127, 77, 60, 154, 28, 240, 17, 65, 68, 234, 95, 194, 170, 34, 212, 222, 32, 54, 151, 46, 19, 205, 3, 119, 7, 23, 117, 104, 89, 172, 214, 182, 228, 44, 121, 85, 84, 52, 138, 165, 229, 236, 201, 47, 9, 78, 227, 210, 202, 74, 6, 11, 167, 161, 196, 133, 171, 137, 39, 147, 66, 129, 158, 5, 174, 219, 232, 139, 116, 0, 97, 143, 218, 58, 245, 188, 226, 18, 155, 197, 135, 107, 177, 42, 200, 149, 166, 136, 181, 86, 163, 72, 70, 100, 156, 190, 162, 103, 164, 235, 91, 113, 131, 178, 230, 111, 43, 192, 49, 30, 169, 87, 168, 106, 98, 183, 90, 141, 130, 27, 40, 71, 57, 12, 124, 185, 238, 1, 20, 13, 4, 81, 73, 247, 217, 176, 45, 26, 239, 186, 67, 132, 175, 208, 253, 150, 193, 198, 248, 22, 37, 241, 94, 126, 88, 8, 14, 224, 102, 199, 38, 36, 128, 92, 16, 231, 63, 146, 237, 83, 191, 233, 24, 115, 225, 209, 246, 223, 251, 252, 118, 215, 25, 93, 101, 189, 29, 122, 114, 61, 75, 76, 153, 10, 206, 50, 195, 55, 203, 250, 179, 125, 21, 187, 220 };
constexpr unsigned char table7[] = { 120, 178, 15, 73, 181, 114, 101, 75, 206, 95, 244, 102, 174, 180, 207, 34, 215, 57, 128, 71, 179, 253, 200, 76, 223, 233, 188, 170, 55, 237, 160, 47, 67, 43, 64, 11, 212, 201, 211, 109, 171, 23, 134, 157, 84, 187, 70, 94, 33, 159, 246, 1, 88, 3, 68, 248, 40, 173, 124, 4, 53, 240, 16, 217, 50, 58, 111, 191, 59, 7, 143, 172, 142, 183, 100, 241, 242, 52, 96, 9, 8, 182, 28, 220, 87, 86, 140, 162, 205, 79, 167, 151, 214, 234, 203, 61, 12, 121, 165, 6, 144, 235, 209, 148, 78, 18, 164, 132, 26, 46, 2, 156, 35, 152, 239, 224, 119, 77, 231, 74, 45, 85, 238, 38, 175, 252, 204, 51, 213, 112, 169, 153, 192, 106, 37, 131, 138, 108, 89, 118, 49, 168, 48, 122, 30, 5, 218, 110, 19, 136, 196, 69, 22, 243, 54, 129, 145, 41, 113, 29, 27, 104, 147, 141, 149, 90, 137, 103, 163, 161, 63, 107, 80, 0, 115, 193, 186, 133, 154, 251, 24, 139, 82, 166, 44, 176, 190, 254, 126, 236, 146, 221, 158, 197, 62, 247, 105, 130, 198, 210, 135, 93, 99, 249, 36, 72, 245, 31, 194, 226, 98, 20, 65, 17, 81, 232, 39, 185, 123, 116, 255, 32, 66, 228, 208, 225, 127, 97, 83, 91, 155, 216, 117, 222, 60, 150, 92, 219, 177, 189, 56, 202, 13, 25, 14, 125, 227, 184, 199, 10, 250, 229, 230, 195, 42, 21 };

constexpr unsigned char udp0[] = {
    162, 252, 144, 251, 70, 71, 238, 152, 10, 65, 122, 60, 53, 98, 202, 5,
    249, 3, 15, 64, 149, 118, 27, 178, 172, 94, 198, 179, 241, 9, 8, 129,
    171, 234, 148, 74, 132, 147, 139, 21, 77, 222, 86, 31, 59, 51, 210, 0,
    228, 194, 250, 124, 73, 204, 93, 243, 61, 227, 42, 163, 2, 236, 87, 13,
    186, 153, 219, 168, 7, 125, 106, 38, 28, 145, 229, 101, 57, 191, 167, 18,
    39, 195, 136, 211, 170, 150, 4, 143, 135, 187, 200, 1, 212, 183, 92, 208,
    127, 81, 49, 68, 230, 245, 34, 30, 95, 103, 141, 169, 158, 213, 107, 173,
    37, 52, 114, 119, 62, 239, 176, 11, 242, 47, 35, 69, 175, 26, 72, 177,
    117, 131, 123, 24, 113, 253, 214, 209, 104, 156, 254, 102, 223, 116, 160, 226,
    206, 108, 54, 12, 80, 79, 100, 237, 88, 244, 23, 83, 248, 115, 218, 22,
    133, 97, 78, 203, 45, 55, 217, 112, 196, 164, 216, 110, 151, 224, 50, 46,
    138, 247, 246, 225, 36, 109, 19, 105, 121, 63, 182, 89, 33, 240, 233, 185,
    193, 17, 56, 120, 90, 20, 67, 16, 32, 134, 220, 43, 6, 205, 180, 76,
    66, 207, 189, 84, 58, 140, 232, 199, 165, 29, 126, 91, 166, 82, 159, 255,
    48, 14, 215, 184, 44, 155, 137, 181, 201, 75, 40, 99, 154, 111, 174, 188,
    190, 192, 128, 41, 85, 96, 235, 25, 197, 130, 221, 142, 161, 157, 231, 146
};

constexpr unsigned char udp1[] = {
    217, 87, 202, 45, 248, 211, 26, 168, 44, 212, 249, 111, 30, 139, 55, 7,
    193, 99, 210, 69, 64, 207, 50, 109, 100, 129, 58, 155, 227, 163, 205, 126,
    91, 176, 79, 201, 39, 246, 25, 164, 234, 63, 107, 88, 85, 125, 123, 14,
    225, 82, 70, 124, 149, 244, 21, 43, 130, 185, 174, 95, 242, 179, 78, 219,
    81, 0, 101, 108, 84, 92, 27, 53, 96, 2, 18, 186, 171, 6, 3, 209,
    251, 240, 167, 54, 141, 75, 151, 113, 181, 56, 77, 158, 28, 147, 204, 143,
    119, 135, 12, 97, 152, 144, 90, 229, 131, 35, 46, 190, 228, 154, 132, 61,
    11, 224, 183, 254, 237, 57, 184, 214, 67, 221, 41, 121, 146, 72, 165, 38,
    166, 103, 198, 243, 112, 13, 105, 142, 231, 162, 195, 175, 128, 106, 4, 118,
    140, 194, 220, 66, 31, 71, 199, 116, 169, 153, 98, 29, 76, 10, 65, 127,
    200, 215, 93, 37, 24, 89, 189, 60, 222, 133, 172, 137, 160, 241, 216, 17,
    16, 22, 20, 94, 5, 213, 253, 117, 188, 47, 150, 232, 15, 223, 1, 161,
    247, 208, 52, 136, 206, 192, 252, 138, 102, 8, 230, 233, 178, 245, 145, 170,
    40, 177, 159, 32, 115, 33, 23, 42, 235, 218, 148, 110, 74, 86, 197, 182,
    48, 34, 122, 36, 83, 196, 9, 250, 134, 120, 62, 59, 51, 156, 236, 73,
    114, 173, 68, 239, 180, 203, 226, 80, 19, 104, 49, 191, 187, 157, 255, 238
};

constexpr unsigned char udp2[] = {
    91, 156, 233, 43, 21, 171, 219, 79, 67, 206, 41, 194, 144, 130, 87, 136,
    83, 30, 196, 64, 232, 238, 26, 174, 38, 242, 100, 167, 253, 234, 45, 29,
    138, 39, 216, 134, 158, 132, 248, 128, 201, 16, 199, 119, 7, 85, 190, 12,
    200, 66, 154, 61, 150, 65, 197, 62, 46, 210, 137, 235, 124, 35, 44, 78,
    95, 208, 9, 77, 27, 163, 176, 52, 192, 112, 10, 204, 47, 113, 251, 203,
    170, 145, 149, 31, 140, 73, 193, 202, 0, 146, 92, 222, 148, 40, 123, 185,
    5, 25, 188, 159, 116, 117, 211, 189, 131, 252, 231, 99, 179, 181, 186, 89,
    53, 115, 249, 120, 42, 198, 239, 161, 109, 114, 48, 250, 110, 19, 24, 244,
    63, 141, 6, 225, 22, 118, 23, 175, 214, 153, 247, 241, 142, 50, 227, 213,
    58, 8, 205, 102, 183, 135, 13, 191, 168, 104, 88, 127, 195, 18, 76, 84,
    105, 98, 245, 215, 28, 101, 129, 230, 15, 209, 177, 2, 229, 111, 180, 20,
    240, 33, 81, 56, 55, 152, 236, 11, 93, 90, 226, 243, 60, 255, 69, 3,
    151, 86, 207, 139, 70, 82, 228, 162, 172, 54, 108, 164, 121, 187, 49, 178,
    122, 125, 217, 254, 237, 51, 96, 126, 212, 97, 1, 246, 218, 32, 147, 14,
    223, 36, 80, 143, 155, 107, 71, 4, 221, 157, 224, 34, 74, 68, 57, 59,
    165, 166, 72, 160, 182, 75, 94, 133, 103, 169, 106, 17, 173, 220, 184, 37
};

constexpr unsigned char udp3[] = {
    88, 218, 171, 191, 231, 96, 130, 44, 145, 66, 74, 183, 47, 150, 223, 168,
    41, 251, 157, 125, 175, 4, 132, 134, 126, 97, 22, 68, 164, 31, 17, 83,
    221, 177, 235, 61, 225, 255, 24, 33, 93, 10, 116, 3, 62, 30, 56, 76,
    122, 206, 141, 213, 71, 112, 201, 180, 179, 238, 144, 239, 188, 51, 55, 128,
    19, 53, 49, 8, 237, 190, 196, 230, 242, 85, 236, 245, 158, 67, 63, 7,
    226, 178, 197, 16, 159, 45, 193, 14, 154, 111, 185, 0, 90, 184, 246, 64,
    214, 217, 161, 107, 26, 165, 147, 248, 153, 160, 250, 229, 202, 120, 124, 173,
    73, 77, 121, 113, 100, 101, 133, 43, 115, 204, 208, 94, 60, 209, 215, 155,
    39, 166, 13, 104, 37, 247, 35, 149, 15, 58, 32, 195, 84, 129, 140, 227,
    12, 81, 89, 222, 92, 82, 52, 192, 181, 137, 50, 228, 1, 233, 36, 99,
    243, 119, 199, 69, 203, 240, 241, 27, 152, 249, 80, 5, 200, 252, 23, 135,
    70, 170, 207, 108, 174, 109, 244, 148, 254, 95, 110, 205, 98, 103, 46, 151,
    72, 86, 11, 156, 18, 54, 117, 42, 48, 40, 87, 79, 75, 146, 9, 194,
    65, 169, 57, 102, 216, 143, 136, 163, 34, 210, 220, 6, 253, 232, 91, 224,
    234, 131, 186, 142, 198, 172, 167, 106, 20, 2, 29, 59, 182, 212, 21, 118,
    176, 139, 25, 187, 127, 162, 219, 138, 38, 114, 123, 78, 105, 28, 211, 189
};

constexpr char tableF[][256] = {
    { 202, 203, 207, 125, 175, 40, 79, 43, 121, 156, 114, 50, 240, 89, 69, 250, 182, 254, 176, 151, 102, 53, 130, 42, 109, 62, 63, 12, 214, 127, 188, 230, 51, 67, 64, 237, 208, 74, 220, 105, 123, 13, 23, 110, 41, 44, 52, 143, 91, 249, 252, 178, 129, 139, 200, 141, 158, 73, 22, 47, 75, 206, 180, 8, 86, 131, 145, 174, 27, 96, 5, 211, 190, 82, 106, 157, 210, 228, 120, 192, 37, 138, 17, 205, 85, 169, 155, 196, 124, 55, 177, 103, 199, 48, 81, 19, 167, 159, 224, 9, 100, 112, 113, 78, 133, 135, 98, 163, 2, 198, 229, 24, 36, 238, 243, 14, 57, 221, 115, 204, 215, 197, 45, 183, 126, 66, 108, 226, 87, 118, 107, 193, 168, 7, 3, 216, 234, 152, 217, 142, 171, 11, 144, 232, 236, 21, 83, 248, 241, 80, 187, 219, 33, 166, 70, 212, 191, 58, 92, 149, 173, 31, 181, 209, 97, 154, 147, 153, 255, 30, 201, 218, 253, 195, 222, 162, 60, 10, 84, 242, 146, 128, 225, 28, 16, 26, 68, 136, 170, 245, 72, 184, 227, 186, 88, 4, 111, 94, 119, 35, 132, 164, 76, 39, 117, 1, 20, 25, 179, 99, 95, 161, 38, 160, 93, 244, 54, 185, 165, 104, 101, 49, 0, 29, 150, 90, 46, 6, 235, 223, 61, 247, 231, 122, 34, 71, 172, 194, 116, 56, 59, 148, 32, 246, 18, 140, 15, 65, 189, 77, 137, 251, 233, 134, 213, 239 },
    { 72, 9, 162, 78, 231, 187, 220, 221, 242, 202, 248, 62, 223, 203, 36, 4, 146, 60, 10, 115, 24, 226, 225, 152, 21, 93, 156, 104, 75, 148, 26, 67, 249, 197, 228, 70, 44, 254, 159, 55, 12, 76, 102, 22, 190, 155, 98, 35, 122, 185, 113, 204, 17, 136, 240, 45, 87, 243, 15, 32, 107, 116, 210, 85, 186, 167, 54, 88, 191, 23, 127, 224, 57, 83, 40, 118, 109, 2, 103, 209, 52, 31, 171, 91, 73, 19, 71, 101, 1, 188, 183, 79, 18, 48, 255, 43, 33, 125, 20, 164, 3, 216, 145, 157, 123, 61, 247, 208, 49, 100, 58, 181, 222, 25, 126, 130, 112, 133, 180, 178, 147, 139, 114, 141, 86, 196, 173, 194, 214, 53, 234, 119, 215, 144, 230, 184, 241, 46, 51, 192, 170, 166, 176, 29, 232, 37, 161, 213, 97, 65, 92, 205, 131, 252, 251, 233, 96, 129, 0, 50, 250, 227, 14, 217, 89, 154, 77, 124, 193, 160, 94, 105, 237, 34, 212, 5, 175, 80, 27, 158, 132, 163, 238, 111, 28, 165, 134, 245, 74, 235, 219, 253, 143, 108, 198, 206, 168, 13, 229, 42, 84, 110, 121, 211, 142, 56, 244, 239, 182, 90, 117, 106, 95, 16, 7, 30, 120, 140, 189, 246, 201, 6, 38, 66, 169, 135, 138, 150, 99, 63, 128, 137, 199, 195, 218, 151, 149, 179, 172, 8, 59, 68, 69, 82, 81, 177, 200, 207, 41, 174, 236, 64, 39, 11, 47, 153 },
    { 77, 215, 241, 25, 14, 192, 94, 139, 46, 248, 128, 32, 213, 145, 22, 51, 172, 251, 142, 144, 126, 47, 95, 29, 97, 158, 76, 66, 33, 223, 108, 150, 146, 35, 187, 189, 105, 129, 239, 54, 28, 202, 57, 111, 193, 225, 102, 78, 168, 147, 2, 237, 98, 191, 42, 120, 89, 219, 155, 68, 36, 1, 41, 27, 109, 171, 183, 250, 236, 24, 210, 207, 154, 244, 55, 235, 16, 106, 62, 159, 188, 253, 245, 180, 112, 11, 21, 199, 39, 48, 71, 162, 134, 18, 212, 121, 153, 252, 229, 169, 156, 133, 60, 174, 61, 205, 132, 184, 201, 87, 58, 195, 157, 63, 64, 115, 255, 127, 70, 217, 0, 59, 124, 167, 88, 34, 9, 26, 224, 75, 220, 110, 173, 17, 254, 218, 15, 6, 43, 85, 249, 216, 90, 151, 118, 116, 208, 211, 232, 152, 84, 135, 221, 181, 74, 137, 114, 194, 67, 200, 79, 50, 161, 247, 226, 37, 166, 214, 131, 140, 163, 117, 7, 182, 198, 238, 209, 80, 38, 170, 96, 30, 49, 206, 45, 149, 13, 204, 240, 141, 186, 177, 10, 179, 119, 138, 82, 242, 246, 93, 83, 197, 125, 8, 123, 3, 91, 107, 136, 19, 243, 196, 148, 20, 73, 40, 178, 164, 234, 233, 4, 165, 190, 113, 104, 23, 12, 100, 176, 222, 44, 99, 53, 160, 72, 143, 230, 231, 203, 86, 175, 5, 56, 52, 92, 81, 228, 101, 227, 65, 31, 130, 185, 122, 103, 69 },
    { 200, 242, 232, 30, 19, 144, 76, 122, 102, 141, 99, 117, 107, 148, 74, 136, 40, 82, 125, 60, 4, 113, 91, 210, 37, 142, 52, 103, 187, 11, 170, 41, 22, 114, 35, 12, 71, 58, 28, 69, 110, 155, 221, 205, 101, 85, 174, 168, 254, 150, 222, 128, 66, 194, 250, 131, 228, 34, 217, 188, 162, 236, 38, 239, 169, 145, 172, 140, 56, 104, 32, 105, 62, 21, 47, 84, 149, 25, 196, 157, 97, 139, 252, 213, 138, 182, 106, 27, 63, 77, 124, 191, 180, 240, 112, 197, 115, 208, 204, 108, 43, 127, 90, 3, 233, 94, 42, 26, 135, 93, 18, 50, 202, 92, 212, 190, 181, 251, 238, 163, 227, 59, 209, 143, 109, 129, 79, 198, 6, 234, 165, 23, 243, 201, 51, 72, 214, 179, 29, 225, 61, 7, 189, 120, 121, 246, 158, 2, 255, 207, 173, 87, 65, 224, 171, 64, 156, 20, 249, 13, 78, 184, 230, 248, 218, 137, 244, 167, 178, 126, 80, 253, 186, 8, 5, 96, 195, 231, 192, 152, 223, 81, 83, 226, 229, 111, 9, 237, 95, 46, 166, 132, 1, 88, 164, 49, 206, 130, 98, 73, 86, 54, 119, 44, 215, 31, 17, 160, 183, 53, 0, 16, 68, 45, 203, 153, 24, 146, 247, 151, 36, 123, 159, 245, 48, 154, 134, 216, 118, 133, 185, 39, 67, 176, 116, 55, 89, 241, 14, 15, 177, 33, 75, 10, 235, 199, 175, 220, 211, 193, 147, 219, 70, 100, 57, 161 },
    { 93, 160, 32, 67, 113, 34, 48, 223, 232, 157, 60, 137, 222, 82, 154, 128, 147, 220, 8, 101, 5, 92, 203, 55, 94, 39, 52, 95, 158, 107, 254, 163, 105, 6, 71, 185, 11, 7, 212, 88, 56, 196, 190, 187, 100, 174, 242, 229, 152, 175, 24, 20, 236, 76, 116, 226, 72, 51, 208, 209, 75, 121, 59, 65, 188, 140, 255, 41, 191, 33, 171, 57, 172, 86, 215, 63, 241, 104, 62, 161, 110, 16, 253, 165, 89, 169, 26, 79, 181, 117, 201, 43, 40, 225, 125, 17, 123, 15, 124, 38, 14, 153, 170, 167, 239, 247, 69, 144, 142, 84, 131, 182, 248, 143, 4, 166, 13, 87, 233, 192, 243, 2, 246, 202, 155, 230, 132, 27, 90, 134, 205, 214, 58, 244, 183, 80, 122, 9, 135, 151, 83, 74, 22, 199, 250, 115, 129, 46, 96, 23, 159, 97, 219, 231, 61, 251, 162, 118, 186, 102, 217, 149, 133, 235, 12, 19, 238, 184, 227, 37, 21, 148, 252, 145, 146, 18, 85, 179, 35, 54, 50, 237, 198, 73, 78, 120, 207, 127, 200, 206, 29, 114, 221, 25, 224, 53, 98, 228, 216, 99, 176, 178, 0, 177, 30, 77, 91, 156, 119, 194, 106, 240, 218, 31, 3, 49, 204, 150, 189, 211, 28, 109, 70, 47, 66, 112, 111, 103, 197, 245, 42, 81, 213, 36, 136, 44, 68, 1, 139, 138, 10, 195, 249, 234, 180, 108, 141, 130, 126, 193, 168, 164, 45, 210, 173, 64 },
    { 92, 49, 176, 31, 113, 30, 105, 56, 44, 40, 154, 193, 206, 123, 21, 53, 216, 166, 37, 242, 139, 164, 17, 178, 228, 86, 0, 112, 132, 39, 59, 141, 162, 100, 58, 194, 208, 255, 124, 205, 238, 128, 198, 209, 97, 147, 190, 150, 171, 212, 135, 29, 192, 138, 188, 215, 14, 43, 33, 34, 232, 9, 133, 23, 226, 82, 240, 237, 20, 183, 145, 78, 140, 222, 214, 134, 161, 254, 102, 48, 89, 246, 200, 217, 41, 7, 248, 146, 187, 72, 103, 210, 125, 236, 243, 185, 25, 73, 36, 108, 169, 70, 116, 81, 111, 55, 167, 57, 85, 95, 76, 52, 225, 98, 62, 127, 221, 3, 64, 159, 109, 51, 158, 142, 231, 5, 101, 16, 32, 156, 201, 199, 47, 69, 157, 244, 182, 118, 74, 137, 119, 15, 143, 46, 26, 75, 67, 18, 224, 173, 175, 207, 252, 93, 203, 8, 121, 110, 218, 22, 196, 104, 83, 50, 160, 144, 253, 68, 54, 90, 181, 170, 149, 120, 126, 245, 165, 4, 96, 87, 2, 45, 153, 197, 114, 241, 239, 179, 71, 136, 148, 42, 186, 250, 249, 189, 234, 230, 155, 11, 19, 91, 80, 191, 122, 151, 163, 94, 180, 211, 204, 79, 84, 24, 1, 10, 227, 88, 28, 131, 233, 220, 219, 202, 60, 35, 168, 115, 99, 177, 65, 61, 235, 13, 247, 184, 27, 38, 172, 66, 117, 107, 77, 129, 195, 12, 213, 174, 223, 130, 106, 229, 152, 251, 6, 63 },
    { 41, 16, 71, 107, 72, 30, 55, 105, 174, 5, 117, 250, 132, 77, 82, 171, 112, 49, 233, 214, 104, 200, 51, 70, 76, 228, 10, 196, 93, 13, 160, 166, 154, 225, 149, 47, 224, 242, 176, 191, 11, 66, 249, 115, 182, 36, 129, 211, 240, 220, 192, 241, 243, 25, 131, 99, 187, 212, 159, 234, 42, 231, 95, 17, 136, 68, 57, 254, 189, 206, 106, 110, 145, 26, 23, 146, 138, 168, 238, 75, 184, 237, 108, 12, 46, 118, 50, 133, 7, 221, 56, 236, 22, 2, 135, 178, 1, 85, 148, 3, 157, 247, 219, 4, 255, 232, 97, 83, 125, 53, 109, 151, 44, 208, 181, 130, 6, 227, 213, 32, 67, 152, 20, 28, 73, 113, 90, 226, 223, 52, 74, 9, 88, 63, 122, 186, 80, 58, 121, 18, 37, 245, 170, 124, 194, 119, 193, 98, 169, 217, 39, 207, 153, 103, 140, 43, 172, 203, 60, 251, 180, 185, 175, 31, 48, 209, 40, 81, 78, 158, 8, 79, 202, 54, 150, 165, 246, 69, 84, 34, 239, 116, 15, 134, 188, 204, 162, 248, 101, 27, 62, 183, 65, 244, 201, 218, 137, 143, 91, 126, 21, 252, 173, 147, 235, 144, 59, 163, 141, 100, 111, 128, 197, 64, 87, 155, 229, 61, 167, 0, 215, 222, 114, 123, 24, 94, 33, 179, 216, 38, 120, 92, 96, 205, 127, 230, 195, 45, 142, 177, 29, 253, 199, 35, 156, 86, 19, 161, 102, 210, 198, 14, 139, 164, 89, 190 },
    { 182, 47, 114, 5, 49, 70, 194, 78, 225, 52, 97, 177, 169, 82, 99, 146, 108, 72, 230, 231, 172, 250, 165, 6, 58, 150, 205, 54, 66, 35, 109, 14, 158, 166, 237, 152, 251, 121, 223, 90, 130, 243, 85, 202, 53, 133, 145, 23, 106, 127, 211, 2, 57, 176, 31, 164, 112, 135, 163, 206, 93, 247, 157, 123, 80, 38, 147, 77, 217, 239, 24, 42, 122, 32, 254, 111, 241, 7, 12, 203, 75, 28, 192, 253, 255, 20, 95, 173, 19, 89, 1, 195, 155, 221, 143, 69, 184, 242, 232, 10, 64, 103, 207, 18, 96, 132, 120, 179, 81, 212, 87, 193, 115, 51, 40, 43, 71, 170, 30, 208, 161, 119, 92, 183, 46, 229, 102, 156, 125, 33, 248, 186, 74, 55, 29, 154, 25, 91, 222, 13, 167, 252, 22, 159, 141, 220, 199, 73, 56, 233, 162, 44, 171, 178, 198, 168, 219, 246, 26, 86, 138, 188, 3, 11, 116, 50, 88, 76, 227, 142, 238, 144, 34, 160, 196, 61, 98, 151, 83, 218, 104, 0, 235, 15, 117, 60, 140, 118, 244, 4, 27, 175, 153, 209, 137, 48, 94, 126, 134, 67, 131, 84, 16, 204, 240, 41, 65, 62, 63, 216, 224, 45, 136, 129, 39, 181, 17, 110, 201, 185, 214, 234, 187, 100, 149, 8, 107, 228, 174, 37, 139, 226, 36, 200, 213, 79, 180, 113, 9, 210, 236, 197, 101, 245, 148, 124, 249, 189, 59, 128, 68, 190, 105, 21, 191, 215 },
    { 48, 93, 87, 124, 47, 69, 101, 194, 128, 204, 181, 170, 253, 180, 172, 145, 80, 158, 16, 166, 71, 109, 72, 129, 6, 40, 83, 144, 0, 135, 206, 245, 37, 67, 41, 179, 112, 146, 8, 1, 5, 235, 168, 123, 12, 213, 216, 13, 138, 217, 176, 187, 78, 198, 219, 90, 63, 74, 85, 113, 44, 248, 29, 151, 226, 34, 89, 100, 103, 221, 64, 207, 162, 137, 142, 232, 60, 214, 150, 143, 161, 56, 54, 136, 195, 17, 147, 2, 82, 174, 247, 66, 230, 205, 73, 53, 30, 55, 233, 130, 32, 164, 215, 42, 116, 117, 27, 141, 188, 39, 223, 108, 224, 149, 22, 31, 200, 228, 7, 175, 243, 236, 189, 126, 26, 160, 36, 182, 178, 122, 105, 35, 165, 254, 57, 84, 155, 249, 19, 238, 208, 148, 173, 154, 77, 220, 202, 3, 218, 197, 61, 95, 23, 152, 183, 25, 11, 131, 184, 79, 65, 192, 97, 20, 111, 250, 21, 159, 201, 225, 244, 106, 191, 18, 76, 222, 81, 114, 46, 211, 157, 125, 231, 92, 70, 169, 38, 121, 186, 229, 28, 94, 153, 255, 185, 209, 115, 196, 163, 240, 251, 110, 119, 107, 132, 177, 86, 227, 171, 104, 68, 91, 140, 24, 62, 102, 246, 203, 49, 237, 14, 59, 99, 210, 118, 9, 134, 10, 156, 96, 120, 33, 190, 193, 242, 252, 133, 43, 4, 234, 15, 139, 98, 75, 58, 45, 199, 241, 52, 239, 167, 88, 51, 212, 50, 127 },
    { 14, 79, 119, 46, 242, 245, 153, 251, 232, 179, 184, 23, 129, 182, 66, 82, 68, 113, 59, 195, 51, 150, 97, 134, 107, 20, 220, 163, 226, 57, 128, 43, 211, 192, 7, 13, 231, 155, 98, 39, 56, 173, 47, 76, 96, 32, 91, 143, 149, 180, 89, 124, 74, 73, 241, 146, 70, 111, 12, 37, 116, 233, 136, 131, 10, 3, 24, 215, 194, 38, 167, 202, 65, 159, 26, 255, 175, 253, 45, 50, 33, 86, 130, 123, 162, 185, 157, 170, 200, 166, 0, 229, 243, 58, 152, 110, 63, 122, 4, 204, 203, 186, 120, 227, 53, 55, 205, 142, 219, 209, 198, 165, 114, 234, 17, 246, 208, 222, 254, 193, 141, 224, 207, 28, 230, 87, 164, 252, 188, 244, 161, 151, 223, 11, 199, 8, 2, 121, 77, 88, 190, 18, 80, 221, 217, 15, 156, 212, 48, 16, 75, 61, 187, 27, 137, 62, 60, 238, 171, 228, 177, 115, 19, 197, 178, 108, 176, 6, 5, 160, 236, 247, 71, 135, 189, 117, 84, 145, 240, 35, 225, 44, 106, 102, 140, 249, 100, 30, 78, 132, 112, 29, 40, 90, 148, 1, 41, 174, 72, 109, 181, 49, 105, 85, 133, 93, 158, 210, 191, 36, 248, 235, 127, 42, 31, 69, 201, 101, 144, 183, 169, 34, 172, 206, 103, 64, 147, 139, 237, 118, 216, 92, 25, 52, 95, 138, 250, 9, 22, 239, 83, 213, 168, 54, 126, 125, 21, 67, 214, 94, 218, 81, 196, 104, 99, 154 },
    { 90, 148, 236, 254, 79, 204, 216, 200, 252, 161, 177, 249, 212, 132, 54, 74, 43, 149, 25, 122, 184, 77, 176, 105, 135, 3, 85, 40, 245, 192, 241, 190, 129, 150, 147, 21, 195, 10, 178, 163, 31, 99, 12, 242, 0, 244, 222, 199, 33, 165, 250, 181, 239, 95, 117, 197, 73, 30, 107, 142, 110, 86, 112, 101, 84, 198, 171, 182, 55, 93, 108, 47, 223, 211, 205, 114, 102, 251, 151, 17, 81, 45, 126, 221, 255, 137, 180, 98, 66, 56, 88, 120, 13, 144, 196, 153, 26, 24, 218, 136, 230, 243, 82, 97, 118, 145, 224, 155, 175, 134, 34, 231, 111, 28, 186, 233, 208, 46, 19, 202, 37, 115, 238, 53, 183, 91, 247, 237, 160, 123, 189, 58, 14, 214, 131, 62, 89, 209, 232, 109, 173, 18, 96, 248, 6, 41, 207, 104, 49, 164, 139, 94, 69, 225, 240, 103, 201, 119, 57, 29, 106, 8, 75, 213, 227, 158, 36, 70, 127, 128, 226, 76, 50, 170, 138, 140, 100, 5, 141, 92, 2, 156, 60, 51, 219, 179, 206, 7, 87, 193, 125, 228, 61, 253, 11, 32, 159, 162, 194, 65, 16, 38, 116, 215, 143, 133, 44, 64, 23, 4, 80, 188, 152, 187, 130, 146, 124, 1, 9, 234, 157, 168, 83, 220, 42, 217, 68, 166, 185, 229, 172, 72, 27, 167, 52, 67, 191, 78, 113, 71, 20, 48, 63, 22, 246, 210, 39, 154, 35, 121, 169, 174, 15, 59, 235, 203 },
    { 112, 230, 78, 209, 49, 55, 233, 163, 27, 46, 145, 201, 40, 121, 115, 98, 50, 176, 150, 192, 111, 29, 36, 23, 151, 247, 194, 128, 38, 189, 63, 140, 99, 48, 51, 174, 206, 17, 183, 88, 119, 172, 161, 159, 127, 203, 9, 210, 22, 173, 2, 74, 168, 75, 155, 213, 85, 252, 15, 122, 141, 195, 32, 90, 178, 94, 165, 102, 139, 62, 242, 44, 37, 41, 69, 1, 166, 202, 108, 100, 154, 73, 58, 188, 226, 197, 12, 147, 248, 204, 199, 24, 116, 225, 131, 92, 87, 28, 101, 217, 60, 249, 95, 64, 13, 237, 222, 93, 7, 200, 65, 104, 184, 221, 56, 83, 207, 224, 190, 57, 53, 54, 211, 10, 125, 198, 42, 160, 234, 208, 182, 82, 219, 245, 45, 6, 106, 81, 244, 144, 76, 26, 238, 186, 181, 124, 33, 251, 191, 229, 5, 137, 77, 239, 68, 79, 142, 18, 136, 123, 31, 66, 157, 35, 61, 185, 253, 25, 149, 20, 70, 21, 72, 135, 158, 177, 214, 30, 164, 19, 4, 130, 255, 193, 114, 59, 250, 52, 138, 162, 148, 240, 227, 118, 126, 133, 103, 218, 156, 205, 43, 110, 97, 132, 129, 231, 105, 187, 109, 254, 39, 47, 80, 0, 84, 212, 241, 215, 223, 107, 180, 235, 143, 146, 179, 153, 117, 91, 243, 170, 236, 67, 169, 71, 8, 171, 3, 152, 232, 220, 196, 11, 246, 89, 34, 175, 228, 96, 113, 134, 14, 216, 86, 120, 16, 167 }
};

void StreamEncryption::decrypt(char* buffer, size_t length)
{
    unsigned char temp;

    for (int i = 0; i < length; i++) {
        switch (m_decryptKey[2] & 3) {
        case 0:
            temp = table2[m_decryptKey[1] ^ buffer[i]];
            break;
        case 1:
            temp = table6[m_decryptKey[1] ^ buffer[i]];
            break;
        case 2:
            temp = m_decryptKey[0] ^ table0[buffer[i]];
            break;
        case 3:
            temp = m_decryptKey[3] ^ table6[buffer[i]];
            break;
        }

        m_decryptKey[0] += m_decryptKey[1];
        m_decryptKey[1] ^= m_decryptKey[3];
        m_decryptKey[2] += table4[buffer[i]];
        m_decryptKey[3] ^= m_decryptKey[2];
        ++m_decryptKey[1];
        ++m_decryptKey[2];
        ++m_decryptKey[3];
        buffer[i] = temp;
    }
}

void StreamEncryption::encrypt(char* buffer, size_t length)
{
    for (int i = 0; i < length; i++) {
        switch (m_encryptKey[2] & 3) {
        case 0:
            buffer[i] = m_encryptKey[1] ^ table3[buffer[i]];
            break;
        case 1:
            buffer[i] = m_encryptKey[1] ^ table7[buffer[i]];
            break;
        case 2:
            buffer[i] = table1[m_encryptKey[0] ^ buffer[i]];
            break;
        case 3:
            buffer[i] = table7[m_encryptKey[3] ^ buffer[i]];
            break;
        }

        m_encryptKey[0] += m_encryptKey[1];
        m_encryptKey[1] ^= m_encryptKey[3];
        m_encryptKey[2] += table4[buffer[i]];
        m_encryptKey[3] ^= m_encryptKey[2];
        ++m_encryptKey[1];
        ++m_encryptKey[2];
        ++m_encryptKey[3];
    }
}

void StreamEncryption::generateServerKeys(char* block, BlockGeneratorId generatorId)
{
    GenerateKeyBlock(block, generatorId);
    ParseKeyBlock(block, m_encryptKey, m_decryptKey);
}

bool StreamEncryption::parseServerKeys(char* block, BlockGeneratorId expectedId)
{
    BlockGeneratorId generator = ParseKeyBlock(block, m_decryptKey, m_encryptKey);
    return generator == expectedId;
}

void DecryptBlock(char* buffer, size_t length)
{
    if (length < 6)
        return;

    int dwCnt = length + (length << 4);

    while (dwCnt > 1) {
        --dwCnt;
        buffer[dwCnt % length] = udp2[udp1[buffer[(dwCnt - 1) % length] ^ udp0[(dwCnt - 1) & 0xFF]] ^ buffer[dwCnt % length]];
    }
}

void EncryptBlock(char* buffer, size_t length)
{
    int dwMax = length + (length << 4);
    int dwCnt = 1;

    if (dwMax == 0)
        return;

    while (dwCnt < dwMax) {
        buffer[dwCnt % length] = udp3[buffer[dwCnt % length]] ^ udp1[udp0[(dwCnt - 1) & 0xFF] ^ buffer[(dwCnt - 1) % length]];
        ++dwCnt;
    }
}

void DecryptCache(char* input, char* output)
{
    // IN: 12 byte xor block + 120 bytes of data
    // OUT: 120 bytes of data
    for (auto i = 0; i <= 108; i += 12) {
        output[i + 0] = input[i + 12] - input[0];
        output[i + 1] = input[i + 13] - input[1];
        output[i + 2] = input[i + 14] ^ input[2];
        output[i + 3] = input[i + 15] - input[3];
        output[i + 4] = input[i + 16] ^ input[4];
        output[i + 5] = input[i + 17] ^ input[5];
        output[i + 6] = input[i + 18] ^ input[6];
        output[i + 7] = input[i + 19] - input[7];
        output[i + 8] = input[i + 20] ^ input[8];
        output[i + 9] = input[i + 21] - input[9];
        output[i + 10] = input[i + 22] - input[10];
        output[i + 11] = input[i + 23] ^ input[11];
        input[0] = tableF[0][input[i + 12]];
        input[1] = tableF[1][input[i + 13]];
        input[2] = tableF[2][input[i + 14]];
        input[3] = tableF[3][input[i + 15]];
        input[4] = tableF[4][input[i + 16]];
        input[5] = tableF[5][input[i + 17]];
        input[6] = tableF[6][input[i + 18]];
        input[7] = tableF[7][input[i + 19]];
        input[8] = tableF[8][input[i + 20]];
        input[9] = tableF[9][input[i + 21]];
        input[10] = tableF[10][input[i + 22]];
        input[11] = tableF[11][input[i + 23]];
    }
}

void MangleKeyBlock(char* block)
{
    block[1] = ~block[1];
    block[2] ^= 240;
    block[3] ^= 15;
    block[4] ^= 119;
    block[5] ^= 119;
    block[6] = ~block[6];
    block[7] ^= 240;
    block[8] ^= 15;
    block[9] ^= 119;
    block[10] ^= 119;
    block[11] = ~block[11];
    block[12] ^= 240;
    block[13] ^= 15;
    block[14] ^= 119;
    block[15] ^= 119;
}

void GenerateKeyBlock(char* block, BlockGeneratorId id)
{
    char baseValue = (std::rand() % 254) + 1;
    std::fill_n(block, 16, baseValue);

    block[4] = block[15] ^ block[13] ^ block[5] ^ block[2];
    block[9] = block[14] ^ block[8] ^ block[1] + static_cast<char>(id);
    block[11] = (block[12] ^ block[10] ^ block[7] ^ block[6] ^ block[3] ^ block[0]) + (static_cast<char>(id) >> 7);
    block[0] = block[0] ^ 87;

    for (int i = 1; i <= 104; ++i) {
        int temp = i & 15;

        if (i % 5 == 0)
            block[temp] ^= block[(temp == 0) ? 15 : temp - 1];
        else
            block[temp] += block[(temp == 0) ? 15 : temp - 1];
    }
}

BlockGeneratorId GetKeyBlockGenerator(char* block)
{
    auto id = GetKeyBlockGeneratorCore(block);

    if (id != BlockGeneratorId::Invalid)
        return id;

    MangleKeyBlock(block);
    return GetKeyBlockGeneratorCore(block);
}

BlockGeneratorId GetKeyBlockGeneratorCore(char const* block)
{
    // Preserve original since it is usually needed again
    char a[16];
    std::copy_n(block, 16, a);

    for (int i = 104; i > 0; --i)
        if (i % 5 == 0)
            a[i & 15] ^= a[(i - 1) & 15];
        else
            a[i & 15] -= a[(i - 1) & 15];

    const char v = a[4];
    const char w = a[15] ^ a[13] ^ a[5] ^ a[2];
    const char x = a[12] ^ a[10] ^ a[7] ^ a[6] ^ a[3] ^ a[0] ^ 87;
    const char y = a[9] - (a[14] ^ a[8] ^ a[1]);
    const char z = a[11] - (y >> 7);

    if (v == w && x == z)
        return static_cast<BlockGeneratorId>(y);

    return BlockGeneratorId::Invalid;
}

BlockGeneratorId ParseKeyBlock(char* block, char* up, char* down)
{
    auto id = GetKeyBlockGenerator(block);

    switch (id) {
    case BlockGeneratorId::PrimaryClient:
    case BlockGeneratorId::PrimaryServer:
        up[0] = block[2] - 104;
        up[1] = block[5];
        up[2] = block[9];
        up[3] = block[11];
        down[0] = block[4] - 103;
        down[1] = block[12];
        down[2] = block[10];
        down[3] = block[7];
        break;
    case BlockGeneratorId::SecondaryClient:
    case BlockGeneratorId::SecondaryServer:
        up[0] = block[7] + 84;
        up[1] = block[3];
        up[2] = block[9];
        up[3] = block[5];
        down[0] = block[2] + 85;
        down[1] = block[8];
        down[2] = block[13];
        down[3] = block[6];
        break;
    case BlockGeneratorId::ChatClient:
    case BlockGeneratorId::ChatServer:
        up[0] = block[7] - 34;
        up[1] = block[3];
        up[2] = block[9];
        up[3] = block[5];
        down[0] = block[2] + 122;
        down[1] = block[8];
        down[2] = block[13];
        down[3] = block[6];
        break;
    }

    return id;
}

} // namespace OpenMX