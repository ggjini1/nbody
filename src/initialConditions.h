#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <system.h>
#include <vec3.h>

struct InitialConditionResult {
    System system;
    std::vector<std::string> labels;
    std::vector<std::string> colors;
    bool legend;
};

InitialConditionResult getInitialConditions(const std::string& initial_condition)
{
    constexpr double SECONDS_PER_DAY = 86400.0;
    constexpr double AU_IN_KM        = 149597870.7;
    const double     CONV            = (SECONDS_PER_DAY * SECONDS_PER_DAY) /
                                        std::pow(AU_IN_KM, 3);   // km^3 s^-2 → AU^3 d^-2

    // GM values in km^3 s^-2 ---------------------------------------------------
    const std::unordered_map<std::string, double> GM_KM_S{{"Sun", 132712440041.279419},
                      {"Mercury",   22031.868551},
                      {"Venus",    324858.592000},
                      {"Earth",    398600.435507},
                      {"Mars",      42828.375816},
                      {"Jupiter",126712764.100000},
                      {"Saturn",  37940584.841800},
                      {"Uranus",   5794556.400000},
                      {"Neptune",  6836527.100580},
                      {"Moon",       4902.800118},
                      {"Pluto",       975.500000},
                      {"Ceres",         62.62890},
                      {"Vesta",         17.288245}};

    // Convert GM → AU^3 d^-2 ---------------------------------------------------
    std::unordered_map<std::string, double> GM_AU_DAY;
    for (const auto& [name, gm] : GM_KM_S) GM_AU_DAY[name] = gm * CONV;

    // Masses in M_sun ----------------------------------------------------------
    std::unordered_map<std::string, double> M_SUN;
    const double GM_SUN = GM_KM_S.at("Sun");
    for (const auto& [name, gm] : GM_KM_S) M_SUN[name] = gm / GM_SUN;

    // Universal constant in the chosen units ------------
    const double G = GM_AU_DAY.at("Sun");

    // Position (AU) and velocity (AU/day) tables ------------------------------
    const std::unordered_map<std::string, vec3> POS{
        {"Sun",     {-7.967955691533730e-03, -2.906227441573178e-03,  2.103054301547123e-04}},
        {"Mercury", {-2.825983269538632e-01,  1.974559795958082e-01,  4.177433558063677e-02}},
        {"Venus",   {-7.232103701666379e-01, -7.948302026312400e-02,  4.042871428174315e-02}},
        {"Earth",   {-1.738192017257054e-01,  9.663245550235138e-01,  1.553901854897183e-04}},
        {"Mars",    {-3.013262392582653e-01, -1.454029331393295e+00, -2.300531433991428e-02}},
        {"Jupiter", { 3.485202469657674e+00,  3.552136904413157e+00, -9.271035442798399e-02}},
        {"Saturn",  { 8.988104223143450e+00, -3.719064854634689e+00, -2.931937777323593e-01}},
        {"Uranus",  { 1.226302417897505e+01,  1.529738792480545e+01, -1.020549026883563e-01}},
        {"Neptune", { 2.983501460984741e+01, -1.793812957956852e+00, -6.506401132254588e-01}},
        {"Pluto",   { 1.720200478843485e+01, -3.034155683573043e+01, -1.729127607100611e+00}},
        {"Ceres",   {-1.103880510367569e+00, -2.533340440444230e+00,  1.220283937721780e-01}},
        {"Vesta",   {-8.092549658731499e-02,  2.558381434460076e+00, -6.695836142398572e-02}}};

    const std::unordered_map<std::string, vec3> VEL{
        {"Sun",     { 4.875094764261564e-06, -7.057133213976680e-06, -4.573453713094512e-08}},
        {"Mercury", {-2.232165900189702e-02, -2.157207103176252e-02,  2.855193410495743e-04}},
        {"Venus",   { 2.034068201002341e-03, -2.020828626592994e-02, -3.945639843855159e-04}},
        {"Earth",   {-1.723001232538228e-02, -2.967721342618870e-03,  6.382125383116755e-07}},
        {"Mars",    { 1.424832259345280e-02, -1.579236181580905e-03, -3.823722796161561e-04}},
        {"Jupiter", {-5.470970658852281e-03,  5.642487338479145e-03,  9.896190602066252e-05}},
        {"Saturn",  { 1.822013845554067e-03,  5.143470425888054e-03, -1.617235904887937e-04}},
        {"Uranus",  {-3.097615358317413e-03,  2.276781932345769e-03,  4.860433222241686e-05}},
        {"Neptune", { 1.676536611817232e-04,  3.152098732861913e-03, -6.877501095688201e-05}},
        {"Pluto",   { 2.802810313667557e-03,  8.492056438614633e-04, -9.060790113327894e-04}},
        {"Ceres",   { 8.978653480111301e-03, -4.873256528198994e-03, -1.807162046049230e-03}},
        {"Vesta",   {-1.017876585480054e-02, -5.452367109338154e-04,  1.255870551153315e-03}}};

    const std::unordered_map<std::string, std::string> COLOR_TABLE{
        {"Sun",      "orange"},
        {"Mercury",  "slategrey"},
        {"Venus",    "wheat"},
        {"Earth",    "skyblue"},
        {"Mars",     "red"},
        {"Jupiter",  "darkgoldenrod"},
        {"Saturn",   "gold"},
        {"Uranus",   "paleturquoise"},
        {"Neptune",  "blue"},
        {"Pluto",    ""},
        {"Ceres",    ""},
        {"Vesta",    ""}};

    // Lambda to manufacture a System from a list of names ---------------------
    auto build_system = [&](const std::vector<std::string>& names) -> System {
        std::vector<vec3> x, v;
        std::vector<double> m;
        for (const auto& n : names) {
            x.push_back(POS.at(n));
            v.push_back(VEL.at(n));
            m.push_back((M_SUN.at(n)));  // M_sun units
        }
        return System(static_cast<int>(names.size()), x, v, m, G);
    };

    //--------------------------------------------------------------------------
    // Pythagorean 3‑body ------------------------------------------------------
    //--------------------------------------------------------------------------
    if (initial_condition == "pyth-3-body") {
        std::vector<vec3> x{{ 1.0,  3.0, 0.0},
                            {-2.0, -1.0, 0.0},
                            { 1.0, -1.0, 0.0}};
        std::vector<vec3> v(3, {0.0, 0.0, 0.0});
        std::vector<double> m{3.0 / G, 4.0 / G, 5.0 / G};

        System sys(static_cast<int>(m.size()), x, v, m, G);
        sys.correctCenterOfMass();
        bool legend = false;

        return {std::move(sys), std::vector<std::string>(3), std::vector<std::string>(3), legend};
    }

    //--------------------------------------------------------------------------
    // Classical 9‑planet solar system ----------------------------------------
    //--------------------------------------------------------------------------
    if (initial_condition == "solar_system") {
        const std::vector<std::string> names{ "Sun","Mercury","Venus","Earth","Mars",
                                      "Jupiter","Saturn","Uranus","Neptune" };
        System sys = build_system(names);
        sys.correctCenterOfMass();

        std::vector<std::string> labels, colors;
        for (const auto& n : names) {
            labels.emplace_back(n);
            colors.emplace_back(COLOR_TABLE.at(n));
        }
        bool legend = true;
        return {std::move(sys), labels, colors, legend};
    }

    //--------------------------------------------------------------------------
    // Solar system + dwarf/asteroid KPIs -------------------------------------
    //--------------------------------------------------------------------------
    if (initial_condition == "solar_system_plus") {
        const std::vector<std::string> names{ "Sun","Mercury","Venus","Earth","Mars",
                                      "Jupiter","Saturn","Uranus","Neptune",
                                      "Pluto","Ceres","Vesta" };
        System sys = build_system(names);
        sys.correctCenterOfMass();

        std::vector<std::string> labels, colors;
        for (const auto& n : names) {
            labels.emplace_back(n);
            colors.emplace_back(COLOR_TABLE.at(n)); // may be empty
        }
        bool legend = true;
        return {std::move(sys), labels, colors, legend};
    }

    throw std::invalid_argument("Initial condition not recognised: " + initial_condition);
}