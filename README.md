# Webhooks_Demo
2345
# GitHub Webhook Listener Setup Guide

A guide for setting up a webhook listener that clones repositories on pull request events.

## Prerequisites
- Git installed.
- GitHub account with repository access
- ngrok for local webhook testing

## Detailed Setup Instructions

### 1. Environment Setup
First, set up your Python environment using Conda:

# Create new conda environment
```bash
# Create new conda environment
conda create -n webhook-env python=3.9

# Activate the environment
conda activate webhook-env

# Install Flask
conda install flask
```


### 2. ngrok Setup
1. Download ngrok from [ngrok.com](https://ngrok.com)
2. Extract the ngrok executable
3. Open a new terminal and run:
```bash

ngrok http 5000
```
4. Copy the generated HTTPS URL (e.g., https://1234-your-ngrok.ngrok.io)
   You'll need this URL for the GitHub webhook configuration


### 3. GitHub Webhook Configuration
1. Go to your GitHub repository
2. Navigate to Settings → Webhooks
3. Click "Add webhook"
4. Configure the webhook:
   - Payload URL: Your ngrok URL + "/webhook"
   - Content type: application/json
   - Select events: Choose "Pull requests"
   - Click "Add webhook"

### 4. Webhook Listener Setup
1. Create webhook_listener.py with the provided code
2. Set your desired LOCAL_REPO_PATH in the code
3. Start the Flask server:

```bash
python webhook_listener.py
```

### 5. Testing the Setup
1. Create a new pull request in your repository.
2. Watch your webhook listener console
3. Verify the repository cloning in your specified LOCAL_REPO_PATH

