


# Docker Setup Guide for FastAPI and MongoDB

## 📌 Introduction
This guide explains how to set up Docker containers for FastAPI and MongoDB, verify that the services are running correctly, and troubleshoot connectivity issues.

---

## 🔹 1. Creating a Docker Network
Before running the containers, create a private Docker network for communication:
```sh
docker network create mynetwork
```

---

## 🔹 2. Running the MongoDB Container
To start the MongoDB container:
```sh
docker run -d --name mongodb --network mynetwork -p 27017:27017 -v "C:/Users/elifr/Studies/tope ai/dis_source_code/Mongo_Db_1:/data/db" mongo:latest
```
**Explanation:**
- `-d` → Run in the background.
- `--name mongodb` → Assigns a name to the container.
- `--network mynetwork` → Connects to the created network.
- `-p 27017:27017` → Maps MongoDB port to the local machine.
- `-v "C:/Users/elifr/.../Mongo_Db_1:/data/db"` → Mounts the local database directory.

Check if the container is running:
```sh
docker ps
```

---

## 🔹 3. Restoring Data in MongoDB
If you need to restore a database backup:
```sh
docker exec -it mongodb mongorestore --db topeai /data/db/topeai
```

Verify the database inside the MongoDB shell:
```sh
docker exec -it mongodb mongosh
```
Once inside, check:
```sh
show dbs
use topeai
show collections
```

---

## 🔹 4. Running the FastAPI Container
Start the FastAPI container:
```sh
docker run -d --name fastapi-app --network mynetwork -p 5000:5000 fastapi-app
```
**Explanation:**
- `-d` → Runs in the background.
- `--name fastapi-app` → Assigns a name to the container.
- `--network mynetwork` → Ensures connectivity with MongoDB.
- `-p 5000:5000` → Maps FastAPI port to the local machine.

Check if the API is running:
```sh
docker ps
```

View API logs:
```sh
docker logs -f fastapi-app
```

---

## 🔹 5. Verifying Connection Between FastAPI and MongoDB
Enter the FastAPI container:
```sh
docker exec -it fastapi-app sh
```
Then, install `ping` and test MongoDB connectivity:
```sh
apt update && apt install -y iputils-ping
ping mongodb
```

If you see a list of databases, the connection is successful! ✅

---

## 🔹 6. Stopping and Removing Containers
To **stop** the running containers:
```sh
docker stop fastapi-app mongodb
```

To **remove** the containers:
```sh
docker rm fastapi-app mongodb
```

---

## 🔹 7. Common Issues & Fixes

### ❌ MongoDB Data Not Loaded
- Ensure the data directory path is correct.
- Check permissions for the `Mongo_Db_1` directory.

### ❌ FastAPI Can't Connect to MongoDB
- Update the connection string to:  
  ```
  mongodb://mongodb:27017/
  ```
  instead of `localhost`.

### ❌ API Is Not Accessible
- Make sure FastAPI listens on `0.0.0.0:5000` (not `127.0.0.1`).

For additional debugging:
```sh
docker logs fastapi-app
```

---

```













# Webhooks_Demo
23456789012
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

