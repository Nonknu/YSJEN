#pragma once

#include "YSJEN/Input.h"

namespace YSJEN {
	class WindowsInput :public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtionPressedImpl(int button)override;
		virtual std::pair<float, float> GetMousePositionImpl()override;
		virtual float GetMouseXImpl()override;
		virtual float GetMouseYImpl()override;
	};

}