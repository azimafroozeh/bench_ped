#ifndef DATASETS_HPP
#define DATASETS_HPP

#include "dataset.hpp"
#include "string"
#include <cstdint>
#include <vector>

namespace dataset {

std::vector<Dataset> datasets = {
    {1,
     "arade4",
     PATHS.DATASETS_1024_SAMPLES_PATH + "arade4.csv", //
     PATHS.DATASETS_1024_DIGITS_PATH + "arade4.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "arade4.csv",
     14,
     10,
     8,
     0,
     0,
     0,
     0,
     24},

    {2,
     "basel_temp_f",
     PATHS.DATASETS_1024_SAMPLES_PATH + "basel_temp_f.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "basel_temp_f.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "basel_temp_f.csv",
     14,
     7, //
     47,
     0,
     0,
     0,
     0,
     28}, // 3 works better than 14

    {3,
     "basel_wind_f",
     PATHS.DATASETS_1024_SAMPLES_PATH + "basel_wind_f.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "basel_wind_f.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "basel_wind_f.csv",
     14,
     7, //
     9,
     0,
     0,
     0,
     0,
     29}, // 3 works better than 14

    {4,
     "bird_migration_f",
     PATHS.DATASETS_1024_SAMPLES_PATH + "bird_migration_f.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "bird_migration_f.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "bird_migration_f.csv",
     14,
     9, //
     2,
     0,
     0,
     0,
     0,
     17}, // 3 works better than 14

    {5,
     "bitcoin_f",
     PATHS.DATASETS_1024_SAMPLES_PATH + "bitcoin_f.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "bitcoin_f.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "bitcoin_f.csv",
     14,
     10, //
     10,
     0,
     0,
     0,
     0,
     25}, // 3 works better than 14

    {6,
     "bitcoin_transactions_f",
     PATHS.DATASETS_1024_SAMPLES_PATH + "bitcoin_transactions_f.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "bitcoin_transactions_f.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "bitcoin_transactions_f.csv", //
     14,
     10,
     11,
     0,
     0,
     0,
     0,
     30},

    {7,
     "city_temperature_f",
     PATHS.DATASETS_1024_SAMPLES_PATH + "city_temperature_f.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "city_temperature_f.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "city_temperature_f.csv",
     14,
     13, //
     0,
     0,
     0,
     0,
     0,
     11}, // 3 works better than 14

    {8,
     "cms1",
     PATHS.DATASETS_1024_SAMPLES_PATH + "cms1.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "cms1.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "cms1.csv", //
     14,
     5,
     10,
     0,
     0,
     0,
     0,
     41},

    {9,
     "cms9",
     PATHS.DATASETS_1024_SAMPLES_PATH + "cms9.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "cms9.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "cms9.csv", //
     16,
     16,
     2,
     0,
     0,
     0,
     0,
     10},

    {10,
     "cms25",
     PATHS.DATASETS_1024_SAMPLES_PATH + "cms25.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "cms25.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "cms25.csv", //
     14,
     4,
     6,
     0,
     0,
     0,
     0,
     42},

    {11,
     "food_prices",
     PATHS.DATASETS_1024_SAMPLES_PATH + "food_prices.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "food_prices.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "food_prices.csv", //
     16,
     12,
     24,
     0,
     0,
     0,
     0,
     23},

    {12,
     "gov10",
     PATHS.DATASETS_1024_SAMPLES_PATH + "gov10.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "gov10.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "gov10.csv",
     3,
     1,
     41,
     0,
     0,
     0,
     0,
     29},

    {13,
     "gov26",
     PATHS.DATASETS_1024_SAMPLES_PATH + "gov26.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "gov26.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "gov26.csv",
     18,
     18,
     0,
     0,
     0,
     0,
     0,
     0},

    {14,
     "gov30",
     PATHS.DATASETS_1024_SAMPLES_PATH + "gov30.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "gov30.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "gov30.csv",
     18,
     18,
     4,
     0,
     0,
     0,
     0,
     0},

    {15,
     "gov31",
     PATHS.DATASETS_1024_SAMPLES_PATH + "gov31.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "gov31.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "gov31.csv",
     18,
     18,
     1,
     0,
     0,
     0,
     0,
     0},

    {16,
     "gov40",
     PATHS.DATASETS_1024_SAMPLES_PATH + "gov40.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "gov40.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "gov40.csv",
     18,
     18,
     3,
     0,
     0,
     0,
     0,
     0},

    {17,
     "medicare1",
     PATHS.DATASETS_1024_SAMPLES_PATH + "medicare1.csv", //
     PATHS.DATASETS_1024_DIGITS_PATH + "medicare1.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "medicare1.csv",
     14,
     5,
     37,
     0,
     0,
     0,
     0,
     38},

    {18,
     "medicare9",
     PATHS.DATASETS_1024_SAMPLES_PATH + "medicare9.csv", //
     PATHS.DATASETS_1024_DIGITS_PATH + "medicare9.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "medicare9.csv",
     16,
     16,
     3,
     0,
     0,
     0,
     0,
     10},

    {19,
     "neon_air_pressure",
     PATHS.DATASETS_1024_SAMPLES_PATH + "neon_air_pressure.csv", //
     PATHS.DATASETS_1024_DIGITS_PATH + "neon_air_pressure.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "neon_air_pressure.csv",
     14,
     9,
     3,
     0,
     0,
     0,
     0,
     16},

    {20,
     "neon_bio_temp_c",
     PATHS.DATASETS_1024_SAMPLES_PATH + "neon_bio_temp_c.csv", //
     PATHS.DATASETS_1024_DIGITS_PATH + "neon_bio_temp_c.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "neon_bio_temp_c.csv",
     14,
     12,
     0,
     0,
     0,
     0,
     0,
     10},

    {21,
     "neon_dew_point_temp",
     PATHS.DATASETS_1024_SAMPLES_PATH + "neon_dew_point_temp.csv", //
     PATHS.DATASETS_1024_DIGITS_PATH + "neon_dew_point_temp.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "neon_dew_point_temp.csv",
     14,
     11,
     6,
     0,
     0,
     0,
     0,
     13},

    {22,
     "neon_pm10_dust",
     PATHS.DATASETS_1024_SAMPLES_PATH + "neon_pm10_dust.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "neon_pm10_dust.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "neon_pm10_dust.csv", //
     14,
     11,
     0,
     0,
     0,
     0,
     0,
     8},

    {23,
     "neon_wind_dir",
     PATHS.DATASETS_1024_SAMPLES_PATH + "neon_wind_dir.csv", //
     PATHS.DATASETS_1024_DIGITS_PATH + "neon_wind_dir.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "neon_wind_dir.csv",
     14,
     12,
     0,
     0,
     0,
     0,
     0,
     16},

    {24,
     "nyc29",
     PATHS.DATASETS_1024_SAMPLES_PATH + "nyc29.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "nyc29.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "nyc29.csv", //
     14,
     1,
     5,
     0,
     0,
     0,
     0,
     42},

    {25,
     "poi_lat",
     PATHS.DATASETS_1024_SAMPLES_PATH + "poi_lat.csv", //
     PATHS.DATASETS_1024_DIGITS_PATH + "poi_lat.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "poi_lat.csv",
     16,
     0,
     157,
     0,
     0,
     0,
     0,
     55},

    {26,
     "poi_lon",
     PATHS.DATASETS_1024_SAMPLES_PATH + "poi_lon.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "poi_lon.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "poi_lon.csv", //
     16,
     0,
     199,
     0,
     0,
     0,
     0,
     56},

    {27,
     "ssd_hdd_benchmarks_f",
     PATHS.DATASETS_1024_SAMPLES_PATH + "ssd_hdd_benchmarks_f.csv",
     PATHS.DATASETS_1024_DIGITS_PATH + "ssd_hdd_benchmarks_f.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "ssd_hdd_benchmarks_f.csv", //
     14,
     13,
     0,
     0,
     0,
     0,
     0,
     17},

    {28,
     "stocks_de",
     PATHS.DATASETS_1024_SAMPLES_PATH + "stocks_de.csv", //
     PATHS.DATASETS_1024_DIGITS_PATH + "stocks_de.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "stocks_de.csv",
     14,
     11,
     5,
     0,
     0,
     0,
     0,
     10},

    {29,
     "stocks_uk",
     PATHS.DATASETS_1024_SAMPLES_PATH + "stocks_uk.csv", //
     PATHS.DATASETS_1024_DIGITS_PATH + "stocks_uk.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "stocks_uk.csv",
     14,
     13,
     0,
     0,
     0,
     0,
     0,
     9},

    {30,
     "stocks_usa_c",
     PATHS.DATASETS_1024_SAMPLES_PATH + "stocks_usa_c.csv", //
     PATHS.DATASETS_1024_DIGITS_PATH + "stocks_usa_c.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "stocks_usa_c.csv",
     14,
     12,
     0,
     0,
     0,
     0,
     0,
     7},

    {30,
     "z_n",
     PATHS.DATASETS_1024_SAMPLES_PATH + "z_n.csv", //
     PATHS.DATASETS_1024_DIGITS_PATH + "z_n.csv",
     PATHS.DATASETS_1024_EXCEPTIONS_PATH + "z_n.csv",
     14,
     12,
     0,
     0,
     0,
     0,
     0,
     7},

};
} // namespace dataset
#endif