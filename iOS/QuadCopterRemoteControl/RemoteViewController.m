//
//  RemoteViewController.m
//  QuadCopterRemoteControl
//
//  Created by Jordan Rouille on 2/8/14.
//  Copyright (c) 2014 anders. All rights reserved.
//

#import "RemoteViewController.h"
#include <arpa/inet.h>

#define ALERT_DISCONNECT 0


@interface RemoteViewController ()

@end

@implementation RemoteViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {
        self.dataToSend = [[NSMutableDictionary alloc] init];
        [self resetData];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    self.sentNotifcationDisplayed = FALSE;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - GCAsyncSocket Delegate Methods

- (void)socket:(GCDAsyncSocket *)sock didAcceptNewSocket:(GCDAsyncSocket *)newSocket
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"ACCEPTED NEW SOCKET" message:nil delegate:nil cancelButtonTitle:@"ok" otherButtonTitles:nil, nil];
    [alert show];
}

- (void)socket:(GCDAsyncSocket *)sock didConnectToHost:(NSString *)host port:(uint16_t)port
{
    [self.connectionButton setTitle:@"Disconnect" forState:UIControlStateNormal];
    [self.connectionStatusLabel setText:@"Connected"];
    [self.ipTextField setEnabled:FALSE];
    [self.portTextField setEnabled:FALSE];
    
    self.timer = [NSTimer scheduledTimerWithTimeInterval:15.0 target:self selector:@selector(timerDidFire) userInfo:nil repeats:TRUE];
}
- (void)socketDidDisconnect:(GCDAsyncSocket *)sock withError:(NSError *)err
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"DISCONNECTED" message:nil delegate:nil cancelButtonTitle:@"ok" otherButtonTitles:nil, nil];
    [alert show];
    
    [self.connectionButton setTitle:@"Connect" forState:UIControlStateNormal];
    [self.connectionStatusLabel setText:@"Disconnected"];
    [self.ipTextField setEnabled:TRUE];
    [self.portTextField setEnabled:TRUE];
    
    [self.timer invalidate];
}
- (void)socket:(GCDAsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"DID READ DATA" message:nil delegate:nil cancelButtonTitle:@"ok" otherButtonTitles:nil, nil];
    [alert show];
}
- (void)socketDidCloseReadStream:(GCDAsyncSocket *)sock
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"STREEAM CLOSED" message:nil delegate:nil cancelButtonTitle:@"ok" otherButtonTitles:nil, nil];
    [alert show];
}
- (void)socket:(GCDAsyncSocket *)sock didReadPartialDataOfLength:(NSUInteger)partialLength tag:(long)tag
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"READ PARTIAL DATA" message:nil delegate:nil cancelButtonTitle:@"ok" otherButtonTitles:nil, nil];
    [alert show];
}
- (void)socket:(GCDAsyncSocket *)sock didWriteDataWithTag:(long)tag
{
    if(!self.sentNotifcationDisplayed)
    {
        self.sentNotifcationDisplayed = TRUE;
        
//        UIView *sentMessage = [[UIView alloc] initWithFrame:CGRectMake(self.view.frame.size.width - 210, 20, 200, 100)];
//        [sentMessage.layer setCornerRadius:10];
//        [sentMessage.layer setBorderColor:[UIColor blackColor].CGColor];
//        [sentMessage.layer setBorderWidth:2];
//        UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, sentMessage.frame.size.width, sentMessage.frame.size.height)];
//        [label setText:@"Message Sent"];
//        [label setTextAlignment:NSTextAlignmentCenter];
//        [sentMessage addSubview:label];
//        [self.view addSubview:sentMessage];
//        
//        [self performSelector:@selector(removeSentView:) withObject:sentMessage afterDelay:1];
    }
}

-(void)removeSentView:(UIView *)viewRef
{
    self.sentNotifcationDisplayed = FALSE;
    [viewRef removeFromSuperview];
}

#pragma mark - Timer

-(void)timerDidFire
{
    NSLog(@"Sending Throttle Value: %.1f", self.throttleControl.value);
    NSData *tempData = [self createPayload];
    [self.controlSocket writeData:tempData withTimeout:0 tag:0];
}

-(NSData *)createPayload
{
    uint8_t throttle = self.throttleControl.value;
    
    uint8_t rollLeft = (((NSNumber *)[self.dataToSend objectForKey:KEY_ROLL_LEFT]).boolValue) ? 0x03 : 0x00;
    uint8_t rollRight = (((NSNumber *)[self.dataToSend objectForKey:KEY_ROLL_RIGHT]).boolValue) ? 0x03 : 0x00;
    
    uint8_t yawLeft = (((NSNumber *)[self.dataToSend objectForKey:KEY_YAW_LEFT]).boolValue) ? 0x03 : 0x00;
    uint8_t yawRight = (((NSNumber *)[self.dataToSend objectForKey:KEY_YAW_RIGHT]).boolValue) ? 0x03 : 0x00;
    
    uint8_t pitchForward = (((NSNumber *)[self.dataToSend objectForKey:KEY_PITCH_FORWARD]).boolValue) ? 0x03 : 0x00;
    uint8_t pitchBackwards = (((NSNumber *)[self.dataToSend objectForKey:KEY_PITCH_BACKWARDS]).boolValue) ? 0x03 : 0x00;
    
    uint8_t partOne = (rollLeft << 6);
    partOne = partOne | (rollRight << 4);
    partOne = partOne | (yawLeft << 2);
    partOne = partOne | (yawRight << 0);
    
    uint8_t partTwo = (pitchForward << 6);
    partOne = partOne | (pitchBackwards << 4);

//    uint8_t throttle = 1;
//    uint8_t partOne = 129;
//    uint8_t partTwo = 255;
    uint8_t byteArray[] = {throttle, partOne, partTwo};
//
    return [NSData dataWithBytes:byteArray length:3];
}

-(void)resetData
{
    [self.dataToSend setObject:@0 forKey:KEY_THROTTLE];
    [self.dataToSend setObject:@FALSE forKey:KEY_ROLL_LEFT];
    [self.dataToSend setObject:@FALSE forKey:KEY_ROLL_RIGHT];
    [self.dataToSend setObject:@FALSE forKey:KEY_PITCH_FORWARD];
    [self.dataToSend setObject:@FALSE forKey:KEY_PITCH_BACKWARDS];
    [self.dataToSend setObject:@FALSE forKey:KEY_YAW_LEFT];
    [self.dataToSend setObject:@FALSE forKey:KEY_YAW_RIGHT];
}

#pragma mark Roll

- (IBAction)rollLeftDidBegin:(UIButton *)sender {
    if(self.controlSocket.isConnected)
        [self.dataToSend setObject:@TRUE forKey:KEY_ROLL_LEFT];
}

- (IBAction)rollLeftDidEnd:(UIButton *)sender {
    if(self.controlSocket.isConnected)
        [self.dataToSend setObject:@FALSE forKey:KEY_ROLL_LEFT];
}

- (IBAction)rollRightDidBegin:(UIButton *)sender {
    if(self.controlSocket.isConnected)
        [self.dataToSend setObject:@TRUE forKey:KEY_ROLL_RIGHT];
}

- (IBAction)rollRightDidEnd:(UIButton *)sender {
    if(self.controlSocket.isConnected)
        [self.dataToSend setObject:@FALSE forKey:KEY_ROLL_RIGHT];
}

#pragma mark Pitch

- (IBAction)pitchForwardDidBegin:(UIButton *)sender {
    if(self.controlSocket.isConnected)
        [self.dataToSend setObject:@TRUE forKey:KEY_PITCH_FORWARD];
}

- (IBAction)pitchForwardDidEnd:(UIButton *)sender {
    if(self.controlSocket.isConnected)
        [self.dataToSend setObject:@FALSE forKey:KEY_PITCH_FORWARD];
}

- (IBAction)pitchBackwardDidBegin:(UIButton *)sender {
    if(self.controlSocket.isConnected)
        [self.dataToSend setObject:@TRUE forKey:KEY_PITCH_BACKWARDS];
}

- (IBAction)pitchBackwardDidEnd:(UIButton *)sender {
    if(self.controlSocket.isConnected)
        [self.dataToSend setObject:@FALSE forKey:KEY_PITCH_BACKWARDS];
}

#pragma mark Yaw

- (IBAction)yawLeftDidBegin:(UIButton *)sender
{
    if(self.controlSocket.isConnected)
        [self.dataToSend setObject:@TRUE forKey:KEY_YAW_LEFT];
}

- (IBAction)yawLeftDidEnd:(UIButton *)sender
{
    if(self.controlSocket.isConnected)
        [self.dataToSend setObject:@FALSE forKey:KEY_YAW_LEFT];
}

- (IBAction)yawRightDidBegin:(UIButton *)sender
{
    if(self.controlSocket.isConnected)
        [self.dataToSend setObject:@TRUE forKey:KEY_YAW_RIGHT];
}

- (IBAction)yawRightDidEnd:(UIButton *)sender
{
    if(self.controlSocket.isConnected)
        [self.dataToSend setObject:@FALSE forKey:KEY_YAW_RIGHT];
}

#pragma mark - Server Connection

-(void)connectToServer
{
    if(self.controlSocket.isConnected)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Are You Sure?" message:@"Are you sure you want to disconnect from the server?" delegate:self cancelButtonTitle:@"No" otherButtonTitles:@"Yes", nil];
        alert.tag = ALERT_DISCONNECT;
        [alert show];
    }
    else
    {
        self.controlSocket = [[GCDAsyncSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_main_queue()];
        
        struct sockaddr_in ip4addr;
        
        ip4addr.sin_family = AF_INET;
        ip4addr.sin_port = htons(self.portTextField.text.integerValue);
        inet_pton(AF_INET, [self.ipTextField.text UTF8String], &ip4addr.sin_addr);
        
        NSData *discoveryHost = [NSData dataWithBytes:&ip4addr length:sizeof(ip4addr)];
        
        NSError *err = nil;
        if (![self.controlSocket connectToAddress:discoveryHost error:&err])
        {
            [self.connectionButton setTitle:@"Connect" forState:UIControlStateNormal];
            [self.connectionStatusLabel setText:@"Disconnected"];
            [self.ipTextField setEnabled:TRUE];
            [self.portTextField setEnabled:TRUE];
        }
        else
        {
            [self.connectionButton setTitle:@"Disconnect" forState:UIControlStateNormal];
            [self.connectionStatusLabel setText:@"Connected"];
            [self.ipTextField setEnabled:FALSE];
            [self.portTextField setEnabled:FALSE];
        }
    }
}

- (IBAction)serverConnectionButton:(id)sender
{
    [self connectToServer];
}

#pragma mark - UIAlertViewDelegate Methods
-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if(alertView.tag == ALERT_DISCONNECT)
    {
        if(buttonIndex != 0)
        {
            [self.controlSocket disconnect];
        }
    }
}
@end
