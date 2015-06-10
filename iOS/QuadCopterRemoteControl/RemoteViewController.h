//
//  RemoteViewController.h
//  QuadCopterRemoteControl
//
//  Created by Jordan Rouille on 2/8/14.
//  Copyright (c) 2014 anders. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GCDAsyncSocket.h"

static NSString const * KEY_THROTTLE = @"throttle";
static NSString const * KEY_YAW_LEFT = @"yawLeft";
static NSString const * KEY_YAW_RIGHT = @"yawRight";
static NSString const * KEY_ROLL_LEFT = @"rollLeft";
static NSString const * KEY_ROLL_RIGHT = @"rollRight";
static NSString const * KEY_PITCH_FORWARD = @"pitchForward";
static NSString const * KEY_PITCH_BACKWARDS = @"pitchBackwards";

@interface RemoteViewController : UIViewController <GCDAsyncSocketDelegate, UIAlertViewDelegate>

//Connection
@property (weak, nonatomic) IBOutlet UITextField *ipTextField;
@property (weak, nonatomic) IBOutlet UITextField *portTextField;
@property (weak, nonatomic) IBOutlet UILabel *connectionStatusLabel;
- (IBAction)serverConnectionButton:(id)sender;
@property (nonatomic, strong) GCDAsyncSocket *controlSocket;
@property (weak, nonatomic) IBOutlet UIButton *connectionButton;

// Data Containers & Timers
@property (nonatomic, strong) NSMutableDictionary *dataToSend;
@property (nonatomic, strong) NSTimer *timer;

// Buttons
@property (weak, nonatomic) IBOutlet UISlider *throttleControl;

- (IBAction)rollLeftDidBegin:(UIButton *)sender;
- (IBAction)rollRightDidBegin:(UIButton *)sender;
- (IBAction)pitchForwardDidBegin:(UIButton *)sender;
- (IBAction)pitchBackwardDidBegin:(UIButton *)sender;
- (IBAction)yawLeftDidBegin:(UIButton *)sender;
- (IBAction)yawRightDidBegin:(UIButton *)sender;

- (IBAction)rollLeftDidEnd:(UIButton *)sender;
- (IBAction)rollRightDidEnd:(UIButton *)sender;
- (IBAction)pitchForwardDidEnd:(UIButton *)sender;
- (IBAction)pitchBackwardDidEnd:(UIButton *)sender;
- (IBAction)yawLeftDidEnd:(UIButton *)sender;
- (IBAction)yawRightDidEnd:(UIButton *)sender;

@property BOOL sentNotifcationDisplayed;


@end
