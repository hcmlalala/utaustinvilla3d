#include "naobehavior.h"
#include "../rvdraw/rvdraw.h"

extern int agentBodyType;

/*
 * Real game beaming.
 * Filling params x y angle
 */
/**/
void NaoBehavior::beam( double& beamX, double& beamY, double& beamAngle ) {
    WorldObjType myNum=(WorldObjType)worldModel->getUNum();
	switch (myNum)
	{
	//����Ա
	case WO_TEAMMATE1:
		beamX = -FIELD_X + 2;
		beamY = 0;
		break;
	//����*3
	case WO_TEAMMATE2:
		beamX = -HALF_FIELD_X / 2;
		beamY = HALF_FIELD_Y / 2;
		break;
	case WO_TEAMMATE3:
		beamX = -HALF_FIELD_X / 2;
		beamY = -HALF_FIELD_Y / 2;
		break;
	case WO_TEAMMATE4:
		beamX = -HALF_FIELD_X / 3;
		beamY = 0;
		break;
	//ǰ��*7
	case WO_TEAMMATE5:
		beamX = -HALF_FIELD_X / 5;
		beamY = -HALF_FIELD_Y / 4 * 3;
		break;
	case WO_TEAMMATE6:
		beamX = -HALF_FIELD_X / 5;
		beamY = -HALF_FIELD_Y / 4 * 2;
		break;
	case WO_TEAMMATE7:
		beamX = -HALF_FIELD_X / 5;
		beamY = -HALF_FIELD_Y / 4 * 1;
		break;
	case WO_TEAMMATE8:
		beamX = -HALF_FIELD_X / 5;
		beamY = -HALF_FIELD_Y / 4 * 0;
		break;
	case WO_TEAMMATE9:
		beamX = -HALF_FIELD_X / 5;
		beamY = HALF_FIELD_Y / 4 * 1;
		break;
	case WO_TEAMMATE10:
		beamX = -HALF_FIELD_X / 5;
		beamY = HALF_FIELD_Y / 4 * 2;
		break;
	case WO_TEAMMATE11:
		beamX = -HALF_FIELD_X / 5;
		beamY = HALF_FIELD_Y / 4 * 3;
		break;
	default:
		break;
	}
    beamAngle = 0;
}


SkillType NaoBehavior::selectSkill() {
    // My position and angle
    //cout << worldModel->getUNum() << ": " << worldModel->getMyPosition() << ",\t" << worldModel->getMyAngDeg() << "\n";

    // Position of the ball
    //cout << worldModel->getBall() << "\n";

    // Example usage of the roboviz drawing system and RVSender in rvdraw.cc.
    // Agents draw the position of where they think the ball is
    // Also see example in naobahevior.cc for drawing agent position and
    // orientation.
    /*
    worldModel->getRVSender()->clear(); // erases drawings from previous cycle
    worldModel->getRVSender()->drawPoint("ball", ball.getX(), ball.getY(), 10.0f, RVSender::MAGENTA);
    */

    // ### Demo Behaviors ###

    // Walk in different directions
    //return goToTargetRelative(VecPosition(1,0,0), 0); // Forward
    //return goToTargetRelative(VecPosition(-1,0,0), 0); // Backward
    //return goToTargetRelative(VecPosition(0,1,0), 0); // Left
    //return goToTargetRelative(VecPosition(0,-1,0), 0); // Right
    //return goToTargetRelative(VecPosition(1,1,0), 0); // Diagonal
    //return goToTargetRelative(VecPosition(0,1,0), 90); // Turn counter-clockwise
    //return goToTargetRelative(VecPdosition(0,-1,0), -90); // Turn clockwise
    //return goToTargetRelative(VecPosition(1,0,0), 15); // Circle

    // Walk to the ball
    //return goToTarget(ball);

    // Turn in place to face ball
    /*double distance, angle;
    getTargetDistanceAndAngle(ball, distance, angle);
    if (abs(angle) > 10) {
      return goToTargetRelative(VecPosition(), angle);
    } else {
      return SKILL_STAND;
    }*/

    // Walk to ball while always facing forward
    //return goToTargetRelative(worldModel->g2l(ball), -worldModel->getMyAngDeg());

    // Dribble ball toward opponent's goal
    //return kickBall(KICK_DRIBBLE, VecPosition(HALF_FIELD_X, 0, 0));

    // Kick ball toward opponent's goal
    //return kickBall(KICK_FORWARD, VecPosition(HALF_FIELD_X, 0, 0)); // Basic kick
    //return kickBall(KICK_IK, VecPosition(HALF_FIELD_X, 0, 0)); // IK kick

    // Just stand in place
    //return SKILL_STAND;

    // Demo behavior where players form a rotating circle and kick the ball
    // back and forth
	WorldObjType myNum = (WorldObjType)worldModel->getUNum();
	switch (myNum)
	{
	case WO_TEAMMATE1:
		return goalie();
		break;
	case WO_TEAMMATE2:
	case WO_TEAMMATE3:
	case WO_TEAMMATE4:
		return guard();
		break;
	case WO_TEAMMATE5:
	case WO_TEAMMATE6:
	case WO_TEAMMATE7:
	case WO_TEAMMATE8:
	case WO_TEAMMATE9:
	case WO_TEAMMATE10:
	case WO_TEAMMATE11:
		return vanguard();
		break;
	default:
		break;
	}
}

SkillType NaoBehavior::goalie()
{
	VecPosition myPosition = worldModel->getMyPosition();
	if (myPosition.getDistanceTo(ball) > 3)
		return SKILL_STAND;
	else
	{
		// Find closest teammate to me
		WorldObjType targetNUM = find_closet_obj_to_target(WO_TEAMMATE2, WO_TEAMMATE11, myPosition);
		WorldObject* target = worldModel->getWorldObject((int)targetNUM);
		
		return kickBall(KICK_FORWARD, target->pos);
	}
}

SkillType NaoBehavior::guard()
{
	VecPosition myPosition = worldModel->getMyPosition();
	WorldObjType myNum = (WorldObjType)worldModel->getUNum();
	VecPosition beamPos;
	switch (myNum)
	{
	case WO_TEAMMATE2:
		beamPos.setX(-HALF_FIELD_X / 2);
		beamPos.setY(HALF_FIELD_Y / 2);
		break;
	case WO_TEAMMATE3:
		beamPos.setX(-HALF_FIELD_X / 2);
		beamPos.setY(-HALF_FIELD_Y / 2);
		break;
	case WO_TEAMMATE4:
		beamPos.setX(-HALF_FIELD_X / 3);
		beamPos.setY(0);
		break;
	default:
		break;
	}
	beamPos.setZ(0);

	if (myPosition.getDistanceTo(ball) > 5 || myPosition.getX() > 0)
	{
		SIM::AngDeg localbeamAngle = atan2Deg(0, myPosition.getX() + 1);//�����Ƿ����Եз�
		if (myPosition.getDistanceTo(beamPos) < 0.25 && abs(localbeamAngle) < 10)
			return SKILL_STAND;
		else if (myPosition.getDistanceTo(beamPos) < 0.5)
			return goToTargetRelative(worldModel->g2l(beamPos), localbeamAngle);
		else
			return goToTarget(beamPos);
	}
	else
	{
		// Find closest player to ball
		WorldObjType is_me = find_closet_obj_to_target(WO_TEAMMATE2, WO_TEAMMATE4, ball);
		
		if (worldModel->getUNum() == (int)is_me)
		{
			// Find closest player to me
			WorldObjType targetNUM = find_closet_obj_to_target(WO_TEAMMATE5, WO_TEAMMATE11, myPosition);
			WorldObject* target = worldModel->getWorldObject((int)targetNUM);
			return kickBall(KICK_FORWARD, target->pos);
		}
		else
			return goToTarget(ball);

	}
}

SkillType NaoBehavior::vanguard()
{
	VecPosition goal(HALF_FIELD_X, 0, 0);
	VecPosition myPosition = worldModel->getMyPosition();
	WorldObjType closetNUM = find_closet_obj_to_target(WO_TEAMMATE5, WO_TEAMMATE11, ball);
	if (worldModel->getUNum() == (int)closetNUM)
		return kickBall(KICK_FORWARD,goal);
	else
	{
		if ((ball.getX() - myPosition.getX()) > 0)
			return goToTarget(myPosition + VecPosition(1, 0, 0));
		else
			return goToTarget(myPosition + VecPosition(-1, 0, 0));

	}
}


/*
 * Demo behavior where players form a rotating circle and kick the ball
 * back and forth
 */


SkillType NaoBehavior::demoKickingCircle() {
    // Parameters for circle
    VecPosition center = VecPosition(-HALF_FIELD_X/2.0, 0, 0);
    double circleRadius = 5.0;
    double rotateRate = 2.5;

    // Find closest player to ball
    int playerClosestToBall = -1;
    double closestDistanceToBall = 10000;
    for(int i = WO_TEAMMATE1; i < WO_TEAMMATE1+NUM_AGENTS; ++i) {
        VecPosition temp;
        int playerNum = i - WO_TEAMMATE1 + 1;
        if (worldModel->getUNum() == playerNum) {
            // This is us
            temp = worldModel->getMyPosition();
        } else {
            WorldObject* teammate = worldModel->getWorldObject( i );
            if (teammate->validPosition) {
                temp = teammate->pos;
            } else {
                continue;
            }
        }
        temp.setZ(0);

        double distanceToBall = temp.getDistanceTo(ball);
        if (distanceToBall < closestDistanceToBall) {
            playerClosestToBall = playerNum;
            closestDistanceToBall = distanceToBall;
        }
    }

    if (playerClosestToBall == worldModel->getUNum()) 
	{
        // Have closest player kick the ball toward the center
        return kickBall(KICK_FORWARD, center);
    }
	else
	{
        // Move to circle position around center and face the center
        VecPosition localCenter = worldModel->g2l(center);//Բ�ľ�������ת�������
        SIM::AngDeg localCenterAngle = atan2Deg(localCenter.getY(), localCenter.getX());//�����Ƿ�����Բ��

        // Our desired target position on the circle
        // Compute target based on uniform number, rotate rate, and time
		// ����Ӧ�ƶ�����Ŀ��λ�ã�Բ�ļ�һ�����λ�ã�
        VecPosition target = center + VecPosition(circleRadius,0,0).rotateAboutZ(360.0/(NUM_AGENTS-1)*(worldModel->getUNum()-(worldModel->getUNum() > playerClosestToBall ? 1 : 0)) + worldModel->getTime()*rotateRate);

        // Adjust target to not be too close to teammates or the ball
		// �㷨����Ŀ��λ�ã���ֹ��ײ
        target = collisionAvoidance(true /*teammate*/, false/*opponent*/, true/*ball*/, 1/*proximity thresh*/, .5/*collision thresh*/, target, true/*keepDistance*/);

        if (me.getDistanceTo(target) < .25 && abs(localCenterAngle) <= 10) {
            // Close enough to desired position and orientation so just stand
			//��Ŀ��ܽ������Բ�ĽǶ�С��10�ȣ������ƶ�
            return SKILL_STAND;
        } else if (me.getDistanceTo(target) < .5) {
            // Close to desired position so start turning to face center
			//��Ŀ������Ƕ�ƫת�ϴ������Ƕȼ���
            return goToTargetRelative(worldModel->g2l(target), localCenterAngle);
        } else {
            // Move toward target location
			//�ƶ���Ŀ��λ��
            return goToTarget(target);
        }
    }
}


