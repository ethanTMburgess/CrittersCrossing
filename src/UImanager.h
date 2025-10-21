#pragma once

class UImanager
{
public:
    UImanager() = default;

    bool yesButtonDown = false;
    bool noButtonDown = false;
    bool stampDown = false;

    bool yesButtonPressed = false;
    bool noButtonPressed = false;
    bool nextButtonPressed = false;
    bool stampPressed = false;

    bool yesStampApplied = false;
    bool noStampApplied = false;

    float ButtonTimer = 0.0f;

    GameObject yesButton;
    GameObject noButton;
    GameObject nextButton;

    GameObject stamp;
    GameObject stampTab;
    GameObject stampShadow;

    GameObject yesStamp;
    GameObject noStamp;
};